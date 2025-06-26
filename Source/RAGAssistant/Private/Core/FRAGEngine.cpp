#include "Core/FRAGEngine.h"
#include "Provider/RAGOllamaProvider.h"
#include "ChromaDB/FChromaDBClient.h"
#include "Utils/FRAGFileUtils.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

FRAGEngine::FRAGEngine()
{
    // Initialize backend clients
    OllamaProvider = TStrongObjectPtr<URAGOllamaProvider>(NewObject<URAGOllamaProvider>());
    OllamaProvider->InitOllamaProvider(TEXT(""), TEXT(""));
    ChromaDBClient = MakeShared<FChromaDBClient>();
}

void FRAGEngine::StartProjectIngestion()
{
    // Step 1 of ingestion: Ensure a collection exists in ChromaDB.
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] Initializing collection 'ember_project' in ChromaDB..."));

    ChromaDBClient->CreateCollection(
        TEXT("ember_project"),
        FChromaDBClient::FOnCreateCollectionSuccess::CreateSP(this, &FRAGEngine::OnCreateCollectionSuccess),
        OnPipelineFailed
    );
}

void FRAGEngine::SubmitQuery(const FString& QueryText)
{
    // This will be implemented in the next phase (RAG Augmentation).
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] RAG query functionality is not yet implemented."));
}

// --- Ingestion Pipeline Implementation ---

void FRAGEngine::OnCreateCollectionSuccess(const FChromaCollectionInfo& CollectionInfo)
{
    CurrentCollectionInfo = CollectionInfo;
    UE_LOG(LogTemp, Log, TEXT("Collection ready: %s (ID: %s)."), *CurrentCollectionInfo.Name, *CurrentCollectionInfo.ID);
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] Collection is ready. Starting file scan and chunking..."));
    ScanAndChunkFiles();
}

void FRAGEngine::ScanAndChunkFiles()
{
    TArray<FString> ScannedFilePaths;
    TArray<FString> AllProjectChunks;

    const TArray<FString> ExtensionsToScan = { TEXT("*.h"), TEXT("*.cpp"), TEXT("*.cs"), TEXT("*.uproject"), TEXT("*.uplugin") };
    const FString ProjectDir = FPaths::ProjectDir();

    // Scan both Source and Plugins directories
    FRAGFileUtils::FindProjectFiles(FPaths::Combine(ProjectDir, TEXT("Source")), ScannedFilePaths, ExtensionsToScan);
    FRAGFileUtils::FindProjectFiles(FPaths::Combine(ProjectDir, TEXT("Plugins")), ScannedFilePaths, ExtensionsToScan);

    TSet<FString> FileSet(ScannedFilePaths);
    ScannedFilePaths = FileSet.Array();

    // Read each file and split into chunks
    for (const FString& FilePath : ScannedFilePaths)
    {
        FString FileContent;
        if (FFileHelper::LoadFileToString(FileContent, *FilePath))
        {
            TArray<FString> Chunks = FRAGFileUtils::ChunkFileContent(FileContent, 40, 5);
            AllProjectChunks.Append(Chunks);
        }
    }

    // If chunks were created, start the embedding process
    if (AllProjectChunks.Num() > 0)
    {
        TempVectorStore.Empty();
        ChunksToProcess = AllProjectChunks;
        TotalChunksToProcess = ChunksToProcess.Num();
        ProcessedChunks = 0;
        ProcessNextChunk();
    }
    else
    {
        OnPipelineFailed.ExecuteIfBound(TEXT("No files found to learn from."));
    }
}

void FRAGEngine::ProcessNextChunk()
{
    // If all chunks are embedded, add them to the database
    if (ProcessedChunks >= TotalChunksToProcess)
    {
        AddEmbeddingsToDB();
        return;
    }

    const FString& CurrentChunk = ChunksToProcess[ProcessedChunks];
    OnProgressUpdate.ExecuteIfBound(FString::Printf(TEXT("[System] Embedding chunk... (%d / %d)"), ProcessedChunks + 1, TotalChunksToProcess));

    // Request embedding for the current chunk
    OllamaProvider->GenerateEmbedding(CurrentChunk,
        URAGOllamaProvider::FOnEmbeddingGenerated::CreateSP(this, &FRAGEngine::OnChunkEmbeddingGenerated),
        OnPipelineFailed);
}

void FRAGEngine::OnChunkEmbeddingGenerated(const TArray<float>& EmbeddingVector)
{
    // Store the result temporarily
    FRAGIndexedChunk IndexedChunk;
    IndexedChunk.ChunkText = ChunksToProcess[ProcessedChunks];
    IndexedChunk.EmbeddingVector = EmbeddingVector;
    TempVectorStore.Add(IndexedChunk);

    UE_LOG(LogTemp, Log, TEXT("Chunk %d embedded successfully."), ProcessedChunks + 1);

    // Process the next chunk
    ProcessedChunks++;
    ProcessNextChunk();
}

void FRAGEngine::AddEmbeddingsToDB()
{
    if (TempVectorStore.Num() == 0)
    {
        OnPipelineFailed.ExecuteIfBound(TEXT("No vectors to add to DB. Embedding process might have failed."));
        return;
    }

    OnProgressUpdate.ExecuteIfBound(FString::Printf(TEXT("[System] Saving %d vectors to ChromaDB..."), TempVectorStore.Num()));

    ChromaDBClient->AddEmbeddings(
        CurrentCollectionInfo.ID,
        TempVectorStore,
        FChromaDBClient::FOnAddEmbeddingsSuccess::CreateSP(this, &FRAGEngine::OnAddEmbeddingsToDBSuccess),
        OnPipelineFailed
    );
}

void FRAGEngine::OnAddEmbeddingsToDBSuccess(const FString& ResponseBody)
{
    const FString ResultMessage = FString::Printf(TEXT("[System] Ingestion complete! %d vectors are now stored permanently in ChromaDB."), TempVectorStore.Num());
    OnProgressUpdate.ExecuteIfBound(ResultMessage);
}

void FRAGEngine::OnIngestionFailed(const FString& ErrorMessage)
{
    // Generic failure handler for the whole pipeline
    OnPipelineFailed.ExecuteIfBound(ErrorMessage);
}


// --- Query Pipeline Callbacks (To be implemented later) ---
void FRAGEngine::OnQuestionEmbeddingGenerated(const TArray<float>& EmbeddingVector) {}
void FRAGEngine::OnQuerySuccess(const TArray<FString>& RetrievedDocs) {}
void FRAGEngine::OnQueryFailed(const FString& ErrorMessage) {}
void FRAGEngine::OnFinalAnswerGenerated(const FString& FinalAnswer) {}
