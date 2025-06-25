#include "FGenerateAPIAdapter.h"
#include "Dom/JsonObject.h"

FString FGenerateAPIAdapter::GetEndpoint() const
{
    return TEXT("/api/generate");
}

TSharedPtr<FJsonObject> FGenerateAPIAdapter::CreateRequestBody(const FString& Model, const FString& Prompt, bool bStream) const
{
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    JsonObject->SetStringField(TEXT("model"), Model);
    JsonObject->SetStringField(TEXT("prompt"), Prompt);
    JsonObject->SetBoolField(TEXT("stream"), bStream);
    return JsonObject;
}

FString FGenerateAPIAdapter::ParseResponseBody(const TSharedPtr<FJsonObject>& JsonObject) const
{
    FString ResponseText;
    if (JsonObject.IsValid())
    {
        JsonObject->TryGetStringField(TEXT("response"), ResponseText);
    }
    return ResponseText;
}