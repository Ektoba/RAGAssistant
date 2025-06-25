#pragma once
#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "RAGOllamaResponseStruct.generated.h"

// chat API의 응답 메시지 구조체
USTRUCT()
struct FRAGResponseMessage
{
    GENERATED_BODY()

    UPROPERTY()
    FString Role;

    UPROPERTY()
    FString Content;

    static FRAGResponseMessage FromJsonObject(TSharedPtr<FJsonObject> JsonObject)
    {
        FRAGResponseMessage Message;
        if (JsonObject.IsValid())
        {
            JsonObject->TryGetStringField(TEXT("role"), Message.Role);
            JsonObject->TryGetStringField(TEXT("content"), Message.Content);
        }
        return Message;
    }
};

// 메인 응답 구조체
USTRUCT()
struct FRAGResponse
{
    GENERATED_BODY()

    // generate API의 응답
    UPROPERTY()
    FString Response;

    // chat API의 응답
    UPROPERTY()
    FRAGResponseMessage Message;

    UPROPERTY()
    FString Model;

    UPROPERTY()
    FString CreatedAt;

    UPROPERTY()
    bool bDone = false;

    // JSON 오브젝트에서 Struct로 데이터를 파싱 (더 똑똑해졌어!)
    static FRAGResponse FromJsonObject(TSharedPtr<FJsonObject> JsonObject, bool bIsChat=true)
    {
        FRAGResponse ResponseData;
        if (JsonObject.IsValid())
        {
            JsonObject->TryGetStringField(TEXT("model"), ResponseData.Model);
            JsonObject->TryGetStringField(TEXT("created_at"), ResponseData.CreatedAt);
            JsonObject->TryGetBoolField(TEXT("done"), ResponseData.bDone);

            if (bIsChat)
            {
                const TSharedPtr<FJsonObject>* MessageObject;
                if (JsonObject->TryGetObjectField(TEXT("message"), MessageObject))
                {
                    ResponseData.Message = FRAGResponseMessage::FromJsonObject(*MessageObject);
                }
            }
            else
            {
                JsonObject->TryGetStringField(TEXT("response"), ResponseData.Response);
            }
        }
        return ResponseData;
    }
};