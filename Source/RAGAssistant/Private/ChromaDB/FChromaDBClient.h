// FChromaDBClient.h

#pragma once

#include "CoreMinimal.h"
#include "Data/RAGDataTypes.h"
#include "Interfaces/IHttpRequest.h"


/**
 * @brief ChromaDB REST API와의 통신을 담당하는 클라이언트 클래스
 */
class FChromaDBClient : public TSharedFromThis<FChromaDBClient>
{
public:
    FChromaDBClient();
public:
    // 1. Create Collection용 델리게이트
    DECLARE_DELEGATE_OneParam(FOnCreateCollectionSuccess, const FChromaCollectionInfo&);
    DECLARE_DELEGATE_OneParam(FOnCreateCollectionFailed, const FString&);

    // 2. Add Embeddings용 델리게이트
    DECLARE_DELEGATE_OneParam(FOnAddEmbeddingsSuccess, const FString&);
    DECLARE_DELEGATE_OneParam(FOnAddEmbeddingsFailed, const FString&);

    // 3. Query Collection용 델리게이트
    DECLARE_DELEGATE_OneParam(FOnQuerySuccess, const TArray<FString>&);
    DECLARE_DELEGATE_OneParam(FOnQueryFailed, const FString&);

public:
    void CreateCollection(const FString& CollectionName, FOnCreateCollectionSuccess OnSuccess, FOnCreateCollectionFailed OnFailed);
    void AddEmbeddings(const FString& CollectionID, const TArray<FRAGIndexedChunk>& Chunks, FOnAddEmbeddingsSuccess OnSuccess, FOnAddEmbeddingsFailed OnFailed);
    void QueryCollection(const FString& CollectionID, const TArray<float>& QueryEmbedding, int32 NumResults, FOnQuerySuccess OnSuccess, FOnQueryFailed OnFailed);

private:
    void OnCreateCollectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnCreateCollectionSuccess OnSuccess, FOnCreateCollectionFailed OnFailed);
    void OnAddEmbeddingsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnAddEmbeddingsSuccess OnSuccess, FOnAddEmbeddingsFailed OnFailed);
    void OnQueryCollectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnQuerySuccess OnSuccess, FOnQueryFailed OnFailed);

private:
    FString BaseUrl;
};