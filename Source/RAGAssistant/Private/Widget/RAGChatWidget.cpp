// SRagChatWidget.cpp

#include "Widget/RAGChatWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SBoxPanel.h"

void SRagChatWidget::Construct(const FArguments& InArgs)
{
    // 1. ⭐️ 새로운 지휘관 FRAGEngine을 생성!
    // MakeShared는 새로운 스마트 포인터 객체를 만드는 가장 효율적인 방법이야.
    RagEngine = MakeShared<FRAGEngine>();

    // 2. ⭐️ 엔진의 델리게이트와 위젯의 핸들러 함수를 연결!
    // .BindSP()는 멤버 함수를 델리게이트에 바인딩할 때 사용하는 안전한 방법이야.
    // 'this' 포인터를 TSharedPtr로 자동 변환해서 수명 문제를 방지해줘.
    RagEngine->OnProgressUpdate.BindSP(this, &SRagChatWidget::HandleProgressUpdate);
    RagEngine->OnNewAIMessage.BindSP(this, &SRagChatWidget::HandleNewAIMessage);
    RagEngine->OnPipelineFailed.BindSP(this, &SRagChatWidget::HandlePipelineFailed);

    // Slate 위젯의 UI 구조를 정의합니다.
    ChildSlot
        [
            SNew(SVerticalBox)

                // 채팅 기록을 보여주는 스크롤 가능한 텍스트 블록입니다.
                + SVerticalBox::Slot()
                .FillHeight(1.0f)
                [
                    SNew(SScrollBox)
                        + SScrollBox::Slot()
                        [
                            SAssignNew(ChatHistoryTextBlock, STextBlock)
                                .Text(FText::FromString(TEXT("RAG 어시스턴트에게 무엇이든 물어보세요...")))
                                .WrapTextAt(500.0f)
                        ]
                ]

            // 사용자 입력을 받는 텍스트 박스입니다.
            + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(0, 5, 0, 5)
                [
                    SAssignNew(PromptInputTextBox, SEditableTextBox)
                        .HintText(NSLOCTEXT("RagChat", "PromptHint", "여기에 프롬프트를 입력하세요..."))
                ]

                // 버튼들을 담는 가로 박스입니다.
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(SHorizontalBox)

                        // '프로젝트 학습' 버튼입니다.
                        + SHorizontalBox::Slot()
                        .FillWidth(1.0f)
                        .Padding(0, 0, 2, 0)
                        [
                            SNew(SButton)
                                .HAlign(HAlign_Center)
                                .Text(NSLOCTEXT("RagChat", "ScanButton", "프로젝트 학습"))
                                .OnClicked(this, &SRagChatWidget::OnScanProjectClicked)
                        ]

                        // '전송' 버튼입니다.
                        + SHorizontalBox::Slot()
                        .FillWidth(1.0f)
                        [
                            SNew(SButton)
                                .HAlign(HAlign_Center)
                                .Text(NSLOCTEXT("RagChat", "SendButton", "전송"))
                                .OnClicked(this, &SRagChatWidget::OnSendClicked)
                        ]
                ]
        ];
}

// ⭐️ 소멸자 구현
SRagChatWidget::~SRagChatWidget()
{
    if (RagEngine.IsValid())
    {
        RagEngine->OnProgressUpdate.Unbind();
        RagEngine->OnNewAIMessage.Unbind();
        RagEngine->OnPipelineFailed.Unbind();
    }
}
FReply SRagChatWidget::OnScanProjectClicked()
{
    // RagEngine에 프로젝트 학습 시작을 요청합니다.
    RagEngine->StartProjectIngestion();
    return FReply::Handled();
}

FReply SRagChatWidget::OnSendClicked()
{
    const FString PromptText = PromptInputTextBox->GetText().ToString();
    if (PromptText.IsEmpty())
    {
        return FReply::Handled();
    }

    // UI에 사용자 질문을 먼저 표시합니다.
    FString NewHistory = ChatHistoryTextBlock->GetText().ToString() + TEXT("\n\n[나]: ") + PromptText;
    ChatHistoryTextBlock->SetText(FText::FromString(NewHistory));
    PromptInputTextBox->SetText(FText());

    // RagEngine에 질문 텍스트를 전달하여 RAG 쿼리를 시작합니다.
    RagEngine->SubmitQuery(PromptText);

    return FReply::Handled();
}

void SRagChatWidget::HandleProgressUpdate(const FString& Message)
{
    // 엔진으로부터 받은 진행 상황 메시지를 채팅창에 표시합니다.
    ChatHistoryTextBlock->SetText(FText::FromString(Message));
}

void SRagChatWidget::HandleNewAIMessage(const FString& Message)
{
    // 현재 채팅 기록의 마지막에 AI의 답변을 추가합니다.
    FString CurrentHistory = ChatHistoryTextBlock->GetText().ToString();
    CurrentHistory += TEXT("\n\n[AI]: ") + Message;
    ChatHistoryTextBlock->SetText(FText::FromString(CurrentHistory));
}

void SRagChatWidget::HandlePipelineFailed(const FString& ErrorMessage)
{
    // 현재 채팅 기록의 마지막에 에러 메시지를 추가합니다.
    FString CurrentHistory = ChatHistoryTextBlock->GetText().ToString();
    CurrentHistory += FString::Printf(TEXT("\n\n[시스템][오류]: %s"), *ErrorMessage);
    ChatHistoryTextBlock->SetText(FText::FromString(CurrentHistory));
}