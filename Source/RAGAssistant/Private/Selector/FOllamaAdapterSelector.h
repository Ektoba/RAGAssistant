#pragma once

#include "CoreMinimal.h"

// Forward Declarations
class IOllamaAPIAdapter;

/**
 * @brief 모델 이름에 따라 적절한 API 어댑터를 생성하는 선택기 클래스
 */
class FOllamaAdapterSelector
{
public:
    /**
     * @brief 모델 이름을 기반으로 적절한 IOllamaAPIAdapter 구현체를 생성하여 반환합니다.
     * @param ModelName 확인할 모델의 전체 이름
     * @return 생성된 어댑터의 TSharedPtr
     */
    static TSharedPtr<IOllamaAPIAdapter> CreateAdapter(const FString& ModelName);
};