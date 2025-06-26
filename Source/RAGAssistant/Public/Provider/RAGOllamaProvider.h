#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h" // UObject를 상속받기 위해 필요
#include "Interfaces/IHttpRequest.h" // HTTP 요청을 위한 헤더
#include "Interfaces/IHttpResponse.h"
#include "Data/RAGOllamaRequestStruct.h" // ⭐ 방금 만든 요청 Struct
#include "Data/RAGOllamaResponseStruct.h" // ⭐ 방금 만든 응답 Struct
#include "RAGOllamaProvider.generated.h"

class IOllamaAPIAdapter; // Ollama API 어댑터 인터페이스를 미리 선언합니다.

// OllamaProvider 클래스는 BaseGenerativeAIProvider를 상속받아 Ollama API와 통신하는 기능을 구현합니다.
// 이 클래스는 Unreal Engine의 UObject를 기반으로 하며, Ollama API와의 상호작용을 위한 메서드를 포함합니다.
// OllamaProvider 클래스는 Unreal Engine의 UObject를 기반으로 하며, Ollama API와의 상호작용을 위한 메서드를 포함합니다.
DECLARE_LOG_CATEGORY_EXTERN(LogRAGOllama, Log, All);

/**
 * @brief Ollama 로컬 LLM과의 통신을 담당하는 Generative AI Provider 클래스입니다.
 * 이 클래스는 기존 플러그인의 다른 Provider (예: OpenAI)와 유사한 방식으로 구현됩니다.
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class RAGASSISTANT_API URAGOllamaProvider : public UObject
{
    GENERATED_BODY()

public:
    // ⭐️ 1. 델리게이트 선언을 클래스 내부로! 그리고 DYNAMIC 제거!
    DECLARE_DELEGATE_OneParam(FOnOllamaCompletionGenerated, const FString& /* GeneratedText */);
    DECLARE_DELEGATE_OneParam(FOnOllamaCompletionFailed, const FString& /* ErrorMessage */);
    DECLARE_DELEGATE_OneParam(FOnEmbeddingGenerated, const TArray<float>&);
public:
    URAGOllamaProvider();

    UFUNCTION(BlueprintCallable, Category = "Ollama Settings")
    void InitOllamaProvider(const FString& InOllamaServerUrl, const FString& InDefaultOllamaModel);

    // ⭐️ 2. GenerateCompletionAsync 함수의 파라미터 타입도 non-const 레퍼런스로 변경!
    void GenerateCompletionAsync(
        const FString& Prompt,
        FOnOllamaCompletionGenerated OnCompletionGenerated,
        FOnOllamaCompletionFailed OnCompletionFailed
    );
    void GenerateEmbedding(const FString& TextToEmbed, FOnEmbeddingGenerated OnEmbeddingGenerated, FOnOllamaCompletionFailed OnEmbeddingFailed);
    UPROPERTY(EditAnywhere, Config, Category = "Ollama Settings")
    FString OllamaServerUrl;

    UPROPERTY(EditAnywhere, Config, Category = "Ollama Settings")
    FString DefaultOllamaModel;

protected:
    void OnGenerateCompletionRequestComplete(
        FHttpRequestPtr Request,
        FHttpResponsePtr Response,
        bool bWasSuccessful,
        FOnOllamaCompletionGenerated OnCompletionGenerated,
        FOnOllamaCompletionFailed OnCompletionFailed,
        TSharedPtr<IOllamaAPIAdapter> Adapter // 어댑터를 전달받음!
    );
    void OnGenerateEmbeddingRequestComplete(
        FHttpRequestPtr Request,
        FHttpResponsePtr Response,
        bool bWasSuccessful,
        FOnEmbeddingGenerated OnEmbeddingGenerated,
        FOnOllamaCompletionFailed OnEmbeddingFailed
    );
private:
    FString CurrentOllamaServerUrl;
    FString CurrentDefaultOllamaModel;
};