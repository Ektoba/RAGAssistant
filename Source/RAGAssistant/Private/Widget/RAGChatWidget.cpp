// SRagChatWidget.cpp
#include "Widget/RAGChatWidget.h"
#include "Provider/RAGOllamaProvider.h"
#include "Utils/FRAGFileUtils.h"
#include "Misc/Paths.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SBoxPanel.h" 

// --- UI 구성 ---

void SRagChatWidget::Construct(const FArguments& InArgs)
{
    OllamaProvider = TStrongObjectPtr<URAGOllamaProvider>(NewObject<URAGOllamaProvider>());
    OllamaProvider->InitOllamaProvider(TEXT(""), TEXT(""));

    ChildSlot
        [
            SNew(SVerticalBox)

                // 1. 채팅 기록창
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

            // 2. 프롬프트 입력창
            + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(0, 5, 0, 5)
                [
                    SAssignNew(PromptInputTextBox, SEditableTextBox)
                        .HintText(NSLOCTEXT("RagChat", "PromptHint", "여기에 프롬프트를 입력하세요..."))
                ]

                // 3. 버튼 영역
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(SHorizontalBox)

                        // '프로젝트 학습' 버튼
                        + SHorizontalBox::Slot()
                        .FillWidth(1.0f)
                        .Padding(0, 0, 2, 0)
                        [
                            SNew(SButton)
                                .HAlign(HAlign_Center)
                                .Text(NSLOCTEXT("RagChat", "ScanButton", "프로젝트 학습"))
                                .OnClicked(this, &SRagChatWidget::OnScanProjectClicked)
                        ]

                        // '전송' 버튼
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

// --- RAG 기능 (파일 스캔 및 임베딩) ---

FReply SRagChatWidget::OnScanProjectClicked()
{
    // 이전 결과들을 초기화
    ScannedFilePaths.Empty();
    AllProjectChunks.Empty();
    VectorStore.Empty();
    ChunksToProcess.Empty();
    TotalChunksToProcess = 0;
    ProcessedChunks = 0;

    const TArray<FString> ExtensionsToScan = { TEXT("*.h"), TEXT("*.cpp"), TEXT("*.cs"), TEXT("*.uproject"), TEXT("*.uplugin") };
    const FString ProjectDir = FPaths::ProjectDir();

    // 1. Source 와 Plugins 폴더에서 파일들을 검색
    const FString SourceDir = FPaths::Combine(ProjectDir, TEXT("Source"));
    FRAGFileUtils::FindProjectFiles(SourceDir, ScannedFilePaths, ExtensionsToScan);
    const FString PluginsDir = FPaths::Combine(ProjectDir, TEXT("Plugins"));
    FRAGFileUtils::FindProjectFiles(PluginsDir, ScannedFilePaths, ExtensionsToScan);

    TSet<FString> FileSet(ScannedFilePaths);
    ScannedFilePaths = FileSet.Array();

    // 2. 찾은 파일들을 청크로 나눔
    for (const FString& FilePath : ScannedFilePaths)
    {
        FString FileContent;
        if (FFileHelper::LoadFileToString(FileContent, *FilePath))
        {
            TArray<FString> Chunks = FRAGFileUtils::ChunkFileContent(FileContent, 40, 5);
            AllProjectChunks.Append(Chunks);
        }
    }

    // 3. 청킹이 완료되면, 임베딩 프로세스 시작
    if (AllProjectChunks.Num() > 0)
    {
        ChunksToProcess = AllProjectChunks;
        TotalChunksToProcess = ChunksToProcess.Num();
        ProcessNextChunk(); // 연쇄 반응 시작!
    }
    else
    {
        ChatHistoryTextBlock->SetText(FText::FromString(TEXT("[시스템] 학습할 파일을 찾지 못했습니다.")));
    }

    return FReply::Handled();
}

void SRagChatWidget::ProcessNextChunk()
{
    if (ProcessedChunks >= TotalChunksToProcess)
    {
        const FString ResultMessage = FString::Printf(TEXT("[시스템] %d개의 청크에 대한 임베딩 완료! 총 %d개의 벡터가 저장되었습니다."), TotalChunksToProcess, VectorStore.Num());
        UE_LOG(LogTemp, Log, TEXT("%s"), *ResultMessage);
        ChatHistoryTextBlock->SetText(FText::FromString(ResultMessage));
        return;
    }

    const FString& CurrentChunk = ChunksToProcess[ProcessedChunks];

    const FString ProgressMessage = FString::Printf(TEXT("[시스템] 임베딩 진행 중... (%d / %d)"), ProcessedChunks + 1, TotalChunksToProcess);
    ChatHistoryTextBlock->SetText(FText::FromString(ProgressMessage));

    OllamaProvider->GenerateEmbedding(
        CurrentChunk,
        URAGOllamaProvider::FOnEmbeddingGenerated::CreateSP(this, &SRagChatWidget::OnChunkEmbeddingGenerated),
        URAGOllamaProvider::FOnOllamaCompletionFailed::CreateSP(this, &SRagChatWidget::OnChunkEmbeddingFailed)
    );
}

void SRagChatWidget::OnChunkEmbeddingGenerated(const TArray<float>& EmbeddingVector)
{
    FRAGIndexedChunk IndexedChunk;
    IndexedChunk.ChunkText = ChunksToProcess[ProcessedChunks];
    IndexedChunk.EmbeddingVector = EmbeddingVector;
    VectorStore.Add(IndexedChunk);

    UE_LOG(LogTemp, Log, TEXT("Chunk %d embedded successfully."), ProcessedChunks + 1);

    ProcessedChunks++;
    ProcessNextChunk();
}

void SRagChatWidget::OnChunkEmbeddingFailed(const FString& ErrorMessage)
{
    UE_LOG(LogTemp, Error, TEXT("Failed to embed chunk %d: %s"), ProcessedChunks + 1, *ErrorMessage);

    ProcessedChunks++;
    ProcessNextChunk();
}


// --- 일반 채팅 기능 ---

FReply SRagChatWidget::OnSendClicked()
{
    const FString PromptText = PromptInputTextBox->GetText().ToString();
    if (PromptText.IsEmpty())
    {
        return FReply::Handled();
    }

    FString NewHistory = ChatHistoryTextBlock->GetText().ToString() + TEXT("\n\n[나]: ") + PromptText;
    ChatHistoryTextBlock->SetText(FText::FromString(NewHistory));
    PromptInputTextBox->SetText(FText());

    ChatHistoryTextBlock->SetText(FText::FromString(NewHistory + TEXT("\n\n[AI]: 생각 중...")));

    OllamaProvider->GenerateCompletionAsync(
        PromptText,
        URAGOllamaProvider::FOnOllamaCompletionGenerated::CreateSP(this, &SRagChatWidget::OnCompletionGenerated),
        URAGOllamaProvider::FOnOllamaCompletionFailed::CreateSP(this, &SRagChatWidget::OnCompletionFailed)
    );

    return FReply::Handled();
}

void SRagChatWidget::OnCompletionGenerated(const FString& GeneratedText)
{
    FString CurrentHistory = ChatHistoryTextBlock->GetText().ToString();
    CurrentHistory.RemoveFromEnd(TEXT("생각 중..."));
    CurrentHistory += GeneratedText;
    ChatHistoryTextBlock->SetText(FText::FromString(CurrentHistory));
}

void SRagChatWidget::OnCompletionFailed(const FString& ErrorMessage)
{
    FString CurrentHistory = ChatHistoryTextBlock->GetText().ToString();
    CurrentHistory.RemoveFromEnd(TEXT("생각 중..."));
    CurrentHistory += FString::Printf(TEXT("[오류]: %s"), *ErrorMessage);
    ChatHistoryTextBlock->SetText(FText::FromString(CurrentHistory));
}