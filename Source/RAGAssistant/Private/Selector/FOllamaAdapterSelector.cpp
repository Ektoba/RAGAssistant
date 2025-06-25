#include "Selector/FOllamaAdapterSelector.h"
#include "Adapter/FChatAPIAdapter.h"
#include "Adapter/FGenerateAPIAdapter.h"

TSharedPtr<IOllamaAPIAdapter> FOllamaAdapterSelector::CreateAdapter(const FString& ModelName)
{
    // 모델 이름에 "-instruct" 또는 "-chat"이 포함되어 있으면 채팅 어댑터를 생성
    if (ModelName.Contains(TEXT("-instruct")) || ModelName.Contains(TEXT("-chat")))
    {
        return MakeShared<FChatAPIAdapter>();
    }

    // 그 외의 경우에는 일반 어댑터를 생성
    return MakeShared<FGenerateAPIAdapter>();
}