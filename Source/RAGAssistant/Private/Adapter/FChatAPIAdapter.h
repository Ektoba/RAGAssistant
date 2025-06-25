#pragma once

#include "Adapter/IOllamaAPIAdapter.h"

/**
 * @brief /api/chat 엔드포인트를 사용하는 채팅/Instruct 모델용 어댑터
 */
class FChatAPIAdapter : public IOllamaAPIAdapter
{
public:
    virtual FString GetEndpoint() const override;
    virtual TSharedPtr<FJsonObject> CreateRequestBody(const FString& Model, const FString& Prompt, bool bStream) const override;
    virtual FString ParseResponseBody(const TSharedPtr<FJsonObject>& JsonObject) const override;
};