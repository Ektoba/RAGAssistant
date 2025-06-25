// SRagChatWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "UObject/StrongObjectPtr.h"

struct FRAGIndexedChunk
{
    FString ChunkText;
    TArray<float> EmbeddingVector;
};

// 클래스 전방 선언
class STextBlock;
class SEditableTextBox;
class URAGOllamaProvider;

class SRagChatWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SRagChatWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TStrongObjectPtr<URAGOllamaProvider> OllamaProvider;
    TSharedPtr<STextBlock> ChatHistoryTextBlock;
    TSharedPtr<SEditableTextBox> PromptInputTextBox;
private:
    FReply OnSendClicked();
    void OnCompletionGenerated(const FString& GeneratedText);
    void OnCompletionFailed(const FString& ErrorMessage);
    FReply OnScanProjectClicked();
private:
    void OnChunkEmbeddingGenerated(const TArray<float>& EmbeddingVector);
    void OnChunkEmbeddingFailed(const FString& ErrorMessage);
    void ProcessNextChunk();
private:
    TArray<FString> ScannedFilePaths;
    TArray<FString> AllProjectChunks;
private:
    int32 TotalChunksToProcess = 0;
    int32 ProcessedChunks = 0;
    TArray<FString> ChunksToProcess;
    TArray<FRAGIndexedChunk> VectorStore;

};