#pragma once
#include "CoreMinimal.h"
#include "Dom/JsonObject.h" // JSON 오브젝트 사용을 위해 필요
#include "RAGOllamaRequestStruct.generated.h"

USTRUCT()
struct FRAGChatMessage
{
    GENERATED_BODY()

    UPROPERTY()
    FString Role; // "system", "user", "assistant"

    UPROPERTY()
    FString Content;
};

USTRUCT()
struct FRAGRequest
{
    GENERATED_BODY()

    UPROPERTY()
    FString Model;

    // 'generate' API를 위한 단일 프롬프트
    UPROPERTY()
    FString Prompt;

    // 'chat' API를 위한 메시지 배열
    UPROPERTY()
    TArray<FRAGChatMessage> Messages;

    UPROPERTY()
    bool bStream = false;

    // 이 Struct를 JSON 오브젝트로 변환하는 함수 (이제 더 똑똑해졌어!)
    TSharedPtr<FJsonObject> ToJsonObject(bool bIsChat = true) const
    {
        TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
        JsonObject->SetStringField(TEXT("model"), Model);
        JsonObject->SetBoolField(TEXT("stream"), bStream);

        if (bIsChat)
        {
            TArray<TSharedPtr<FJsonValue>> MessageArray;
            for (const FRAGChatMessage& Message : Messages)
            {
                TSharedPtr<FJsonObject> MessageObject = MakeShared<FJsonObject>();
                MessageObject->SetStringField(TEXT("role"), Message.Role);
                MessageObject->SetStringField(TEXT("content"), Message.Content);
                MessageArray.Add(MakeShared<FJsonValueObject>(MessageObject));
            }
            JsonObject->SetArrayField(TEXT("messages"), MessageArray);
        }
        else
        {
            JsonObject->SetStringField(TEXT("prompt"), Prompt);
        }
        return JsonObject;
    }
};