#pragma once

#include "IOllamaAPIAdapter.h" // 우리가 만든 인터페이스!

/**
 * @brief /api/generate 엔드포인트를 사용하는 일반 모델용 어댑터
 */
class FGenerateAPIAdapter : public IOllamaAPIAdapter
{
public:
    virtual FString GetEndpoint() const override;
    virtual TSharedPtr<FJsonObject> CreateRequestBody(const FString& Model, const FString& Prompt, bool bStream) const override;
    virtual FString ParseResponseBody(const TSharedPtr<FJsonObject>& JsonObject) const override;
};