// SRagChatWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Data/RAGDataTypes.h"
#include "UObject/StrongObjectPtr.h"

// 클래스 전방 선언
class STextBlock;
class SEditableTextBox;
class URAGOllamaProvider;
class FChromaDBClient;

class SRagChatWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SRagChatWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    // --- 멤버 변수 ---
    TStrongObjectPtr<URAGOllamaProvider> OllamaProvider;
    TSharedPtr<FChromaDBClient> ChromaDBClient;
    TSharedPtr<STextBlock> ChatHistoryTextBlock;
    TSharedPtr<SEditableTextBox> PromptInputTextBox;

    FChromaCollectionInfo CurrentCollectionInfo;
    TArray<FString> ScannedFilePaths;
    TArray<FString> ChunksToProcess;
    TArray<FRAGIndexedChunk> VectorStore;
    int32 TotalChunksToProcess = 0;
    int32 ProcessedChunks = 0;

    // --- RAG 기능 함수 (콜백 함수들의 시그니처를 새로운 설계에 맞게 수정!) ---
    FReply OnScanProjectClicked();
    void ScanAndChunkFiles(const FChromaCollectionInfo& CollectionInfo);
    void ProcessNextChunk();
    void OnChunkEmbeddingGenerated(const TArray<float>& EmbeddingVector);
    void OnChunkEmbeddingFailed(const FString& ErrorMessage);
    void AddEmbeddingsToDB();
    void OnAddEmbeddingsSuccess(const FString& ResponseBody);
    void OnAddEmbeddingsFailed(const FString& ErrorMessage);
    // ⭐️ CreateCollection 실패 시 전용 콜백 함수 추가
    void OnCreateCollectionFailed(const FString& ErrorMessage);


    // --- 일반 채팅 기능 함수 ---
    FReply OnSendClicked();
    void OnCompletionGenerated(const FString& GeneratedText);
    void OnCompletionFailed(const FString& ErrorMessage);
};