#include "Provider/RAGOllamaProvider.h"
#include "HttpModule.h"                      // HTTP 요청을 위해 필요
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"        // IHttpResponse에서 HTTP 상태 코드와 내용 가져오기
#include "Serialization/JsonSerializer.h"    // JSON 직렬화/역직렬화를 위해 필요
#include "Dom/JsonObject.h"                  // FJsonObject 사용을 위해 필요
#include "Models/Ollama/RAGOllamaRequestStruct.h" 
#include "Models/Ollama/RAGOllamaResponseStruct.h" 
#include "Adapter/IOllamaAPIAdapter.h"       // Ollama API 어댑터 인터페이스
#include "Selector/FOllamaAdapterSelector.h" // Ollama 어댑터 선택기
// 로그 카테고리 정의
DEFINE_LOG_CATEGORY(LogRAGOllama);

URAGOllamaProvider::URAGOllamaProvider()
{
    // 생성자에서 Ollama 서버의 기본 URL과 모델 이름을 설정합니다.
    // 이 값들은 언리얼 에디터의 프로젝트 세팅에서 변경할 수 있습니다.
    OllamaServerUrl = TEXT("http://localhost:11434"); // Ollama 기본 URL
    DefaultOllamaModel = TEXT("deepseek-coder-v2:latest");
}

// InitOllamaProvider 함수 구현
void URAGOllamaProvider::InitOllamaProvider(const FString& InOllamaServerUrl, const FString& InDefaultOllamaModel)
{
    // 외부에서 전달된 값으로 내부 멤버 변수를 업데이트합니다.
    // 만약 전달된 값이 비어있으면, UPROPERTY로 설정된 기본값을 사용합니다.
    CurrentOllamaServerUrl = InOllamaServerUrl.IsEmpty() ? OllamaServerUrl : InOllamaServerUrl;
    CurrentDefaultOllamaModel = InDefaultOllamaModel.IsEmpty() ? DefaultOllamaModel : InDefaultOllamaModel;

    UE_LOG(LogRAGOllama, Log, TEXT("Ollama Provider Initialized. Server URL: %s, Model: %s"), *CurrentOllamaServerUrl, *CurrentDefaultOllamaModel);
}

// GenerateCompletionAsync 함수 구현 (비동기식 - 권장!)
void URAGOllamaProvider::GenerateCompletionAsync(
    const FString& Prompt,
    FOnOllamaCompletionGenerated OnCompletionGenerated,
    FOnOllamaCompletionFailed OnCompletionFailed
)
{
    UE_LOG(LogRAGOllama, Log, TEXT("Async Ollama Completion requested. Prompt: %s"), *Prompt);

    // Ollama 서버 URL과 모델이 설정되어 있는지 확인
    if (CurrentOllamaServerUrl.IsEmpty() || CurrentDefaultOllamaModel.IsEmpty())
    {
        FString ErrorMsg = TEXT("Ollama Provider is not initialized. Please call InitOllamaProvider first or set values in Project Settings.");
        UE_LOG(LogRAGOllama, Error, TEXT("%s"), *ErrorMsg);
        OnCompletionFailed.ExecuteIfBound(ErrorMsg);
        return;
    }

    const bool bIsChatModel = CurrentDefaultOllamaModel.Contains(TEXT("-instruct")) || CurrentDefaultOllamaModel.Contains(TEXT("-chat"));
    const FString Endpoint = bIsChatModel ? TEXT("/api/chat") : TEXT("/api/generate");

    // ⭐️ 1. Selector에게 모델에 맞는 어댑터를 만들어달라고 요청!
    TSharedPtr<IOllamaAPIAdapter> Adapter = FOllamaAdapterSelector::CreateAdapter(CurrentDefaultOllamaModel);
    if (!Adapter.IsValid())
    {
        OnCompletionFailed.ExecuteIfBound(TEXT("Failed to create a valid API adapter."));
        return;
    }

    // 2. HTTP 요청 생성
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    FString CleanURL = CurrentOllamaServerUrl;
    CleanURL.RemoveFromEnd(TEXT("/"));

    // ⭐️ 3. 어댑터에게 엔드포인트와 요청 본문을 만들어달라고 시킴!
    HttpRequest->SetURL(FString::Printf(TEXT("%s%s"), *CleanURL, *Adapter->GetEndpoint()));
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    TSharedPtr<FJsonObject> RequestBodyJson = Adapter->CreateRequestBody(CurrentDefaultOllamaModel, Prompt, false);

    FString RequestBody;
    FJsonSerializer::Serialize(RequestBodyJson.ToSharedRef(), TJsonWriterFactory<TCHAR>::Create(&RequestBody));
    HttpRequest->SetContentAsString(RequestBody);

    UE_LOG(LogRAGOllama, Log, TEXT("Requesting to Endpoint: %s"), *Adapter->GetEndpoint());
    // ⭐️ 4. 콜백 함수에 우리가 사용한 어댑터를 함께 넘겨줌
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &URAGOllamaProvider::OnGenerateCompletionRequestComplete, OnCompletionGenerated, OnCompletionFailed, Adapter);
    HttpRequest->ProcessRequest();
}

// OnGenerateCompletionRequestComplete 함수 구현 (콜백)
void URAGOllamaProvider::OnGenerateCompletionRequestComplete(
    FHttpRequestPtr Request,
    FHttpResponsePtr Response,
    bool bWasSuccessful, // 이 변수가 네트워크 요청 성공/실패 여부를 알려줘요!
    FOnOllamaCompletionGenerated OnCompletionGenerated,
    FOnOllamaCompletionFailed OnCompletionFailed,
    TSharedPtr<IOllamaAPIAdapter> Adapter
)
{
    // bWasSuccessful이 true이고 응답이 유효한 경우
    if (bWasSuccessful && Response.IsValid())
    {
        UE_LOG(LogRAGOllama, Log, TEXT("Response Received. WasSuccessful: %s"), bWasSuccessful ? TEXT("true") : TEXT("false"));
        if (Response.IsValid())
        {
            UE_LOG(LogRAGOllama, Warning, TEXT("Response Code: %d"), Response->GetResponseCode());
            UE_LOG(LogRAGOllama, Warning, TEXT("Raw Response Body: %s"), *Response->GetContentAsString());
        }

        int32 ResponseCode = Response->GetResponseCode();
        if (ResponseCode >= 200 && ResponseCode < 300) // HTTP 상태 코드가 200번대(성공)인지 확인
        {
            FString ResponseBody = Response->GetContentAsString();
            UE_LOG(LogRAGOllama, Log, TEXT("Ollama Response received (Code: %d): %s"), ResponseCode, *ResponseBody);

            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseBody);

            // JSON 응답을 파싱
            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                const FString ReplyText = Adapter->ParseResponseBody(JsonObject);
                OnCompletionGenerated.ExecuteIfBound(ReplyText);
            }
            else
            {
                OnCompletionFailed.ExecuteIfBound(TEXT("Failed to parse JSON response."));
            }
        }
        else // HTTP 상태 코드가 200번대가 아닌 경우 (예: 400 Bad Request, 500 Internal Server Error 등)
        {
            FString ErrorMessage = FString::Printf(TEXT("HTTP Error: %d - %s"), ResponseCode, *Response->GetContentAsString());
            UE_LOG(LogRAGOllama, Error, TEXT("%s"), *ErrorMessage);
            OnCompletionFailed.ExecuteIfBound(ErrorMessage);
        }
    }
    else // 네트워크 요청 자체(bWasSuccessful)가 실패했거나 응답 객체가 유효하지 않은 경우
    {
        FString ErrorMessage = TEXT("Ollama HTTP Request Failed: Network issue or invalid response.");
        // Request->GetErrorString() 같은 구체적인 오류 문자열은 IHttpRequest 인터페이스에 없습니다.
        // 이 경우, 네트워크 연결 상태나 Ollama 서버의 구동 여부를 직접 확인해야 합니다.
        UE_LOG(LogRAGOllama, Error, TEXT("%s"), *ErrorMessage);
        OnCompletionFailed.ExecuteIfBound(ErrorMessage);
    }
}

void URAGOllamaProvider::GenerateEmbedding(
    const FString& TextToEmbed,
    FOnEmbeddingGenerated OnEmbeddingGenerated,
    FOnOllamaCompletionFailed OnEmbeddingFailed)
{
    // 임베딩 모델 이름을 하드코딩. 나중엔 이것도 설정으로 뺄 수 있겠지?
    const FString EmbeddingModelName = TEXT("nomic-embed-text");

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    FString CleanURL = CurrentOllamaServerUrl;
    CleanURL.RemoveFromEnd(TEXT("/"));

    // 엔드포인트는 /api/embeddings
    HttpRequest->SetURL(FString::Printf(TEXT("%s/api/embeddings"), *CleanURL));
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    // 요청 본문 JSON 생성
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    JsonObject->SetStringField(TEXT("model"), EmbeddingModelName);
    JsonObject->SetStringField(TEXT("prompt"), TextToEmbed);

    FString RequestBody;
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<TCHAR>::Create(&RequestBody));
    HttpRequest->SetContentAsString(RequestBody);

    // 새 콜백 함수를 바인딩
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &URAGOllamaProvider::OnGenerateEmbeddingRequestComplete, OnEmbeddingGenerated, OnEmbeddingFailed);
    HttpRequest->ProcessRequest();
}

// ⭐️ 5. 임베딩 요청 콜백 함수의 구현부
void URAGOllamaProvider::OnGenerateEmbeddingRequestComplete(
    FHttpRequestPtr Request,
    FHttpResponsePtr Response,
    bool bWasSuccessful,
    FOnEmbeddingGenerated OnEmbeddingGenerated,
    FOnOllamaCompletionFailed OnEmbeddingFailed)
{
    if (bWasSuccessful && Response.IsValid() && Response->GetResponseCode() == 200)
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
        {
            const TArray<TSharedPtr<FJsonValue>>* EmbeddingArrayJson;
            if (JsonObject->TryGetArrayField(TEXT("embedding"), EmbeddingArrayJson))
            {
                TArray<float> EmbeddingVector;
                for (const TSharedPtr<FJsonValue>& Value : *EmbeddingArrayJson)
                {
                    EmbeddingVector.Add(Value->AsNumber());
                }
                // 성공! 숫자 배열(벡터)을 델리게이트로 전달
                OnEmbeddingGenerated.ExecuteIfBound(EmbeddingVector);
                return; // 성공했으니 함수 종료
            }
        }
    }

    // 위 모든 과정에서 하나라도 실패했을 경우
    FString ErrorMessage = TEXT("Failed to generate embedding.");
    if (Response.IsValid())
    {
        ErrorMessage += FString::Printf(TEXT(" Response Code: %d, Body: %s"), Response->GetResponseCode(), *Response->GetContentAsString());
    }
    OnEmbeddingFailed.ExecuteIfBound(ErrorMessage);
}

