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
#include "ChromaDB/FChromaDBClient.h"

// --- UI 구성 ---
void SRagChatWidget::Construct(const FArguments& InArgs)
{
    OllamaProvider = TStrongObjectPtr<URAGOllamaProvider>(NewObject<URAGOllamaProvider>());
    OllamaProvider->InitOllamaProvider(TEXT(""), TEXT(""));
    ChromaDBClient = MakeShared<FChromaDBClient>();

    ChildSlot
        [
            SNew(SVerticalBox)

                // 채팅 기록창
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

            // 프롬프트 입력창
            + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(0, 5, 0, 5)
                [
                    SAssignNew(PromptInputTextBox, SEditableTextBox)
                        .HintText(NSLOCTEXT("RagChat", "PromptHint", "여기에 프롬프트를 입력하세요..."))
                ]

                // 버튼 영역
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(SHorizontalBox)

                        + SHorizontalBox::Slot()
                        .FillWidth(1.0f)
                        .Padding(0, 0, 2, 0)
                        [
                            SNew(SButton)
                                .HAlign(HAlign_Center)
                                .Text(NSLOCTEXT("RagChat", "ScanButton", "프로젝트 학습"))
                                .OnClicked(this, &SRagChatWidget::OnScanProjectClicked)
                        ]

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

// --- RAG 기능 (파일 스캔, 청킹, 임베딩, DB 저장) ---

FReply SRagChatWidget::OnScanProjectClicked()
{
    ChatHistoryTextBlock->SetText(FText::FromString(TEXT("[시스템] ChromaDB에 'ember_project' 컬렉션을 생성하거나 가져옵니다...")));

    // ⭐️ 모든 델리게이트를 새로운 짝에 맞게 연결!
    ChromaDBClient->CreateCollection(
        TEXT("ember_project"),
        FChromaDBClient::FOnCreateCollectionSuccess::CreateSP(this, &SRagChatWidget::ScanAndChunkFiles),
        FChromaDBClient::FOnCreateCollectionFailed::CreateSP(this, &SRagChatWidget::OnCreateCollectionFailed)
    );

    return FReply::Handled();
}

void SRagChatWidget::ScanAndChunkFiles(const FChromaCollectionInfo& CollectionInfo)
{
    // 컬렉션 정보를 멤버 변수에 저장
    CurrentCollectionInfo = CollectionInfo;

    UE_LOG(LogTemp, Log, TEXT("Collection ready: %s (ID: %s). Starting file scan."), *CurrentCollectionInfo.Name, *CurrentCollectionInfo.ID);
    ChatHistoryTextBlock->SetText(FText::FromString(TEXT("[시스템] 컬렉션 준비 완료. 프로젝트 파일 스캔 및 청킹을 시작합니다...")));

    // ⭐️⭐️⭐️ 내가 빼먹었던 바로 그 로직! ⭐️⭐️⭐️

    // 1. 이전 결과 초기화
    ScannedFilePaths.Empty();

    // 2. 검색할 확장자 정의
    const TArray<FString> ExtensionsToScan = { TEXT("*.h"), TEXT("*.cpp"), TEXT("*.cs"), TEXT("*.uproject"), TEXT("*.uplugin") };
    const FString ProjectDir = FPaths::ProjectDir();

    // 3. Source 와 Plugins 폴더 검색
    const FString SourceDir = FPaths::Combine(ProjectDir, TEXT("Source"));
    FRAGFileUtils::FindProjectFiles(SourceDir, ScannedFilePaths, ExtensionsToScan);
    const FString PluginsDir = FPaths::Combine(ProjectDir, TEXT("Plugins"));
    FRAGFileUtils::FindProjectFiles(PluginsDir, ScannedFilePaths, ExtensionsToScan);

    TSet<FString> FileSet(ScannedFilePaths);
    ScannedFilePaths = FileSet.Array();

    // 4. 각 파일을 읽고 청크로 나눠서 AllProjectChunks 배열에 추가
    for (const FString& FilePath : ScannedFilePaths)
    {
        FString FileContent;
        if (FFileHelper::LoadFileToString(FileContent, *FilePath))
        {
            TArray<FString> Chunks = FRAGFileUtils::ChunkFileContent(FileContent, 40, 5);
            AllProjectChunks.Append(Chunks);
        }
    }

    // 5. 청킹이 완료되면, 연쇄 임베딩 시작
    if (AllProjectChunks.Num() > 0)
    {
        VectorStore.Empty();
        ChunksToProcess = AllProjectChunks;
        TotalChunksToProcess = ChunksToProcess.Num();
        ProcessedChunks = 0;
        ProcessNextChunk(); // 연쇄 반응 시작!
    }
    else
    {
        ChatHistoryTextBlock->SetText(FText::FromString(TEXT("[시스템] 학습할 파일을 찾지 못했습니다.")));
    }
}

void SRagChatWidget::ProcessNextChunk()
{
    if (ProcessedChunks >= TotalChunksToProcess)
    {
        AddEmbeddingsToDB();
        return;
    }

    const FString& CurrentChunk = ChunksToProcess[ProcessedChunks];
    const FString ProgressMessage = FString::Printf(TEXT("[시스템] 임베딩 진행 중... (%d / %d)"), ProcessedChunks + 1, TotalChunksToProcess);
    ChatHistoryTextBlock->SetText(FText::FromString(ProgressMessage));

    OllamaProvider->GenerateEmbedding(CurrentChunk,
        URAGOllamaProvider::FOnEmbeddingGenerated::CreateSP(this, &SRagChatWidget::OnChunkEmbeddingGenerated),
        URAGOllamaProvider::FOnOllamaCompletionFailed::CreateSP(this, &SRagChatWidget::OnChunkEmbeddingFailed));
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

void SRagChatWidget::AddEmbeddingsToDB()
{
    if (VectorStore.Num() == 0)
    {
        ChatHistoryTextBlock->SetText(FText::FromString(TEXT("[시스템] DB에 저장할 벡터가 없습니다.")));
        return;
    }

    ChatHistoryTextBlock->SetText(FText::FromString(FString::Printf(TEXT("[시스템] %d개의 벡터를 ChromaDB에 저장합니다..."), VectorStore.Num())));

    // ⭐️ 이제 이름 대신, 저장해뒀던 컬렉션 ID를 사용!
    ChromaDBClient->AddEmbeddings(
        CurrentCollectionInfo.ID,
        VectorStore,
        FChromaDBClient::FOnChromaDBSuccess::CreateSP(this, &SRagChatWidget::OnAddEmbeddingsSuccess),
        FChromaDBClient::FOnChromaDBFailed::CreateSP(this, &SRagChatWidget::OnAddEmbeddingsFailed)
    );
}

void SRagChatWidget::OnAddEmbeddingsSuccess(const FString& ResponseBody)
{
    const FString ResultMessage = FString::Printf(TEXT("[시스템] ChromaDB 저장 완료! 총 %d개의 벡터가 영구적으로 저장되었습니다. 이제 질문할 수 있습니다."), VectorStore.Num());
    UE_LOG(LogTemp, Log, TEXT("%s"), *ResultMessage);
    ChatHistoryTextBlock->SetText(FText::FromString(ResultMessage));
}

void SRagChatWidget::OnAddEmbeddingsFailed(const FString& ErrorMessage)
{
    const FString ResultMessage = FString::Printf(TEXT("[시스템][오류] ChromaDB 저장 실패: %s"), *ErrorMessage);
    UE_LOG(LogTemp, Error, TEXT("%s"), *ResultMessage);
    ChatHistoryTextBlock->SetText(FText::FromString(ResultMessage));
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