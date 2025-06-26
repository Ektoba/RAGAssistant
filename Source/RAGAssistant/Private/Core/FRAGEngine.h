#pragma once 

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"
#include "Data/RAGDataTypes.h"

class URAGOllamaProvider;
class FChromaDBClient;

class FRAGEngine : public TSharedFromThis<FRAGEngine>
{
public:
    FRAGEngine();

    /** Delegate to report progress updates to the UI. */
    DECLARE_DELEGATE_OneParam(FOnProgressUpdate, const FString& /* Message */);
    /** Delegate to report the final AI-generated answer to the UI. */
    DECLARE_DELEGATE_OneParam(FOnNewAIMessage, const FString& /* Message */);
    /** Delegate to report any critical pipeline failure to the UI. */
    DECLARE_DELEGATE_OneParam(FOnPipelineFailed, const FString& /* ErrorMessage */);

    FOnProgressUpdate OnProgressUpdate;
    FOnNewAIMessage OnNewAIMessage;
    FOnPipelineFailed OnPipelineFailed;

public:
    /** Starts the entire data ingestion pipeline: Scan -> Chunk -> Embed -> Store. */
    void StartProjectIngestion();

    /** Starts the RAG query pipeline: Embed Query -> Search DB -> Augment -> Generate. */
    void SubmitQuery(const FString& QueryText);

private:
    // --- Private Callbacks for the Ingestion Pipeline ---
    void OnCreateCollectionSuccess(const FChromaCollectionInfo& CollectionInfo);
    void ScanAndChunkFiles();
    void ProcessNextChunk();
    void OnChunkEmbeddingGenerated(const TArray<float>& EmbeddingVector);
    void OnAddEmbeddingsToDBSuccess(const FString& ResponseBody);

    // --- Private Callbacks for the Query Pipeline ---
    void OnQuestionEmbeddingGenerated(const TArray<float>& EmbeddingVector);
    void OnQuerySuccess(const TArray<FString>& RetrievedDocs);
    void OnQueryFailed(const FString& ErrorMessage);

    // --- Private Members: Services and State ---
    TStrongObjectPtr<URAGOllamaProvider> OllamaProvider;
    TSharedPtr<FChromaDBClient> ChromaDBClient;

    FChromaCollectionInfo CurrentCollectionInfo;
    TArray<FRAGIndexedChunk> TempVectorStore;
    TArray<FString> ChunksToProcess;
    int32 TotalChunksToProcess = 0;
    int32 ProcessedChunks = 0;
    FString LastQuestion;
};