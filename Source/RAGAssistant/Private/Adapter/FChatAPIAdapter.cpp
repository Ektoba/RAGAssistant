// FChatAPIAdapter.cpp

#include "FChatAPIAdapter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Models/Ollama/RAGOllamaRequestStruct.h"
#include "Models/Ollama/RAGOllamaResponseStruct.h"


FString FChatAPIAdapter::GetEndpoint() const
{
    return TEXT("/api/chat");
}

TSharedPtr<FJsonObject> FChatAPIAdapter::CreateRequestBody(const FString& Model, const FString& Prompt, bool bStream) const
{
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    JsonObject->SetStringField(TEXT("model"), Model);
    JsonObject->SetBoolField(TEXT("stream"), bStream);

    // 채팅 API는 'messages' 배열 형식을 사용
    TArray<TSharedPtr<FJsonValue>> MessageArray;

    TSharedPtr<FJsonObject> MessageObject = MakeShared<FJsonObject>();
    MessageObject->SetStringField(TEXT("role"), TEXT("user"));
    MessageObject->SetStringField(TEXT("content"), Prompt);

    MessageArray.Add(MakeShared<FJsonValueObject>(MessageObject));

    JsonObject->SetArrayField(TEXT("messages"), MessageArray);

    return JsonObject;
}

FString FChatAPIAdapter::ParseResponseBody(const TSharedPtr<FJsonObject>& JsonObject) const
{
    FString ResponseText;
    if (JsonObject.IsValid())
    {
        // 채팅 API의 응답은 'message' 객체 안의 'content' 필드에 담겨있음
        const TSharedPtr<FJsonObject>* MessageObject;
        if (JsonObject->TryGetObjectField(TEXT("message"), MessageObject))
        {
            (*MessageObject)->TryGetStringField(TEXT("content"), ResponseText);
        }
    }
    return ResponseText;
}