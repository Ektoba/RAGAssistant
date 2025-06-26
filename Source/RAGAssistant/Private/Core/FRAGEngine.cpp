// FRAGEngine.cpp (수정 완료!)

#include "Core/FRAGEngine.h"
#include "Provider/RAGOllamaProvider.h"
#include "ChromaDB/FChromaDBClient.h"
#include "Utils/FRAGFileUtils.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

FRAGEngine::FRAGEngine()
{
    OllamaProvider = TStrongObjectPtr<URAGOllamaProvider>(NewObject<URAGOllamaProvider>());
    OllamaProvider->InitOllamaProvider(TEXT(""), TEXT(""));
    ChromaDBClient = MakeShared<FChromaDBClient>();
}

void FRAGEngine::StartProjectIngestion()
{
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] ChromaDB에서 'ember_project' 컬렉션을 초기화하는 중..."));
    ChromaDBClient->CreateCollection(
        TEXT("ember_project"),
        FChromaDBClient::FOnCreateCollectionSuccess::CreateSP(this, &FRAGEngine::OnCreateCollectionSuccess),
        OnPipelineFailed
    );
}

void FRAGEngine::SubmitQuery(const FString& QueryText)
{
    LastQuestion = QueryText;
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] 질문을 이해하기 위해 벡터로 변환하는 중..."));
    OllamaProvider->GenerateEmbedding(
        QueryText,
        URAGOllamaProvider::FOnEmbeddingGenerated::CreateSP(this, &FRAGEngine::OnQuestionEmbeddingGenerated),
        OnPipelineFailed
    );
}

void FRAGEngine::OnCreateCollectionSuccess(const FChromaCollectionInfo& CollectionInfo)
{
    CurrentCollectionInfo = CollectionInfo;
    UE_LOG(LogTemp, Log, TEXT("Collection ready: %s (ID: %s)."), *CurrentCollectionInfo.Name, *CurrentCollectionInfo.ID);
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] 컬렉션 준비 완료. 파일 스캔 및 청킹을 시작합니다..."));
    ScanAndChunkFiles();
}

void FRAGEngine::ScanAndChunkFiles()
{
    TArray<FString> ScannedFilePaths;
    TArray<FString> AllProjectChunks;
    const TArray<FString> ExtensionsToScan = { TEXT("*.h"), TEXT("*.cpp"), TEXT("*.cs"), TEXT("*.uproject"), TEXT("*.uplugin") };
    const FString ProjectDir = FPaths::ProjectDir();
    FRAGFileUtils::FindProjectFiles(FPaths::Combine(ProjectDir, TEXT("Source")), ScannedFilePaths, ExtensionsToScan);
    FRAGFileUtils::FindProjectFiles(FPaths::Combine(ProjectDir, TEXT("Plugins")), ScannedFilePaths, ExtensionsToScan);
    TSet<FString> FileSet(ScannedFilePaths);
    ScannedFilePaths = FileSet.Array();
    for (const FString& FilePath : ScannedFilePaths)
    {
        FString FileContent;
        if (FFileHelper::LoadFileToString(FileContent, *FilePath))
        {
            TArray<FString> Chunks = FRAGFileUtils::ChunkFileContent(FileContent, 40, 5);
            AllProjectChunks.Append(Chunks);
        }
    }

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
        OnPipelineFailed.ExecuteIfBound(TEXT("학습할 파일을 찾지 못했습니다."));
    }
}

void FRAGEngine::ProcessNextChunk()
{
    if (ProcessedChunks >= TotalChunksToProcess)
    {
        AddEmbeddingsToDB();
        return;
    }
    const FString& CurrentChunk = ChunksToProcess[ProcessedChunks];
    OnProgressUpdate.ExecuteIfBound(FString::Printf(TEXT("[System] 임베딩 진행 중... (%d / %d)"), ProcessedChunks + 1, TotalChunksToProcess));
    OllamaProvider->GenerateEmbedding(CurrentChunk,
        URAGOllamaProvider::FOnEmbeddingGenerated::CreateSP(this, &FRAGEngine::OnChunkEmbeddingGenerated),
        OnPipelineFailed);
}

void FRAGEngine::OnChunkEmbeddingGenerated(const TArray<float>& EmbeddingVector)
{
    FRAGIndexedChunk IndexedChunk;
    IndexedChunk.ChunkText = ChunksToProcess[ProcessedChunks];
    IndexedChunk.EmbeddingVector = EmbeddingVector;
    TempVectorStore.Add(IndexedChunk);
    UE_LOG(LogTemp, Log, TEXT("Chunk %d embedded successfully."), ProcessedChunks + 1);
    ProcessedChunks++;
    ProcessNextChunk();
}

void FRAGEngine::AddEmbeddingsToDB()
{
    if (TempVectorStore.Num() == 0)
    {
        OnPipelineFailed.ExecuteIfBound(TEXT("DB에 추가할 벡터가 없습니다."));
        return;
    }
    OnProgressUpdate.ExecuteIfBound(FString::Printf(TEXT("[System] %d개의 벡터를 ChromaDB에 저장하는 중..."), TempVectorStore.Num()));
    ChromaDBClient->AddEmbeddings(
        CurrentCollectionInfo.ID,
        TempVectorStore,
        FChromaDBClient::FOnAddEmbeddingsSuccess::CreateSP(this, &FRAGEngine::OnAddEmbeddingsToDBSuccess),
        OnPipelineFailed
    );
}

void FRAGEngine::OnAddEmbeddingsToDBSuccess(const FString& ResponseBody)
{
    const FString ResultMessage = FString::Printf(TEXT("[System] 학습 완료! %d개의 벡터가 영구적으로 저장되었습니다."), TempVectorStore.Num());
    OnProgressUpdate.ExecuteIfBound(ResultMessage);
}

void FRAGEngine::OnQuestionEmbeddingGenerated(const TArray<float>& EmbeddingVector)
{
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] 관련된 코드 조각을 DB에서 찾는 중..."));

    // FChromaDBClient를 사용하여 DB에 쿼리를 요청합니다.
    ChromaDBClient->QueryCollection(
        CurrentCollectionInfo.ID,       // 검색할 컬렉션의 ID
        EmbeddingVector,                // 질문의 임베딩 벡터
        5,                              // 가장 관련성 높은 결과 5개를 요청
        FChromaDBClient::FOnQuerySuccess::CreateSP(this, &FRAGEngine::OnQuerySuccess),
        FChromaDBClient::FOnQueryFailed::CreateSP(this, &FRAGEngine::OnQueryFailed)
    );
}

void FRAGEngine::OnQuerySuccess(const TArray<FString>& RetrievedDocs)
{
    OnProgressUpdate.ExecuteIfBound(TEXT("[System] 관련 정보를 바탕으로 답변을 생성하는 중..."));

    // 컨텍스트와 질문을 조합하여 최종 프롬프트를 만듭니다.
    FString ContextString;
    for (const FString& Doc : RetrievedDocs)
    {
        ContextString += Doc + TEXT("\n\n---\n\n");
    }

    const FString FinalPrompt = FString::Printf(
        TEXT("You are a helpful Unreal Engine C++ expert assistant. Answer the user's question based on the provided code context.\n\n")
        TEXT("=== CONTEXT ===\n%s\n\n=== QUESTION ===\n%s\n\n=== ANSWER ==="),
        *ContextString,
        *LastQuestion
    );

    // 최종 프롬프트를 Ollama에 보내 답변 생성을 요청합니다.
    OllamaProvider->GenerateCompletionAsync(
        FinalPrompt,
        URAGOllamaProvider::FOnOllamaCompletionGenerated::CreateSP(this, &FRAGEngine::OnFinalAnswerGenerated),
        OnPipelineFailed
    );
}

void FRAGEngine::OnQueryFailed(const FString& ErrorMessage)
{
    OnPipelineFailed.ExecuteIfBound(FString::Printf(TEXT("DB 검색 실패: %s"), *ErrorMessage));
}

void FRAGEngine::OnFinalAnswerGenerated(const FString& FinalAnswer)
{
    OnNewAIMessage.ExecuteIfBound(FinalAnswer);
}

void FRAGEngine::OnIngestionFailed(const FString& ErrorMessage)
{
    OnPipelineFailed.ExecuteIfBound(ErrorMessage);
}