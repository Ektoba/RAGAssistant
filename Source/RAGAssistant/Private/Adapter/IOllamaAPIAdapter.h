#pragma once

#include "CoreMinimal.h"

class FJsonObject;

/**
 * @brief Ollama API 호출 방식을 정의하는 어댑터 인터페이스 (추상 기본 클래스)
 * 이 클래스를 상속받는 모든 구체적인 어댑터 클래스는 아래의 순수 가상 함수들을 반드시 구현해야 합니다.
 */
class IOllamaAPIAdapter
{
public:
    virtual ~IOllamaAPIAdapter() = default;

    /**
     * @brief 모델 타입에 맞는 API 엔드포인트 문자열을 반환합니다. (예: "/api/generate")
     * @return FString 엔드포인트 경로
     */
    virtual FString GetEndpoint() const = 0;

    /**
     * @brief API 요청에 필요한 JSON 본문을 생성합니다.
     * @param Model 사용할 모델 이름
     * @param Prompt 사용자의 프롬프트
     * @param bStream 스트리밍 여부
     * @return 요청 본문으로 사용될 FJsonObject
     */
    virtual TSharedPtr<FJsonObject> CreateRequestBody(const FString& Model, const FString& Prompt, bool bStream) const = 0;

    /**
     * @brief API 응답으로 온 JSON 객체를 파싱하여 최종 텍스트를 추출합니다.
     * @param JsonObject API로부터 받은 응답 JSON 객체
     * @return AI가 생성한 최종 응답 텍스트
     */
    virtual FString ParseResponseBody(const TSharedPtr<FJsonObject>& JsonObject) const = 0;
};