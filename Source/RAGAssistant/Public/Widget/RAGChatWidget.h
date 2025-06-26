// SRagChatWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Core/FRAGEngine.h" // ⭐️ FRAGEngine 헤더를 포함!
#include "UObject/StrongObjectPtr.h"

// 클래스 전방 선언
class STextBlock;
class SEditableTextBox;
// class URAGOllamaProvider; // 이제 필요 없음
// class FChromaDBClient; // 이제 필요 없음

class SRagChatWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SRagChatWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    // ⭐️ 소멸자 추가! 엔진과의 델리게이트 바인딩을 안전하게 해제해주는 게 좋아.
    ~SRagChatWidget();

private:
    // --- UI 위젯 ---
    TSharedPtr<STextBlock> ChatHistoryTextBlock;
    TSharedPtr<SEditableTextBox> PromptInputTextBox;

    // --- 핵심 로직 담당 ---
    // ⭐️ 이제 위젯은 엔진에 대한 포인터 하나만 가지면 돼!
    TSharedPtr<FRAGEngine> RagEngine;

    // --- UI 이벤트 핸들러 ---
    FReply OnScanProjectClicked();
    FReply OnSendClicked();

    // --- FRAGEngine의 델리게이트에 연결할 함수들 ---
    void HandleProgressUpdate(const FString& Message);
    void HandleNewAIMessage(const FString& Message);
    void HandlePipelineFailed(const FString& ErrorMessage);
};