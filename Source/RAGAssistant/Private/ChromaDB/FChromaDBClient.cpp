#include "ChromaDB/FChromaDBClient.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"

FChromaDBClient::FChromaDBClient()
{
    BaseUrl = TEXT("http://localhost:8000");
}

// ⭐️ 시그니처가 FOnCreateCollectionFailed 로 변경!
void FChromaDBClient::CreateCollection(const FString& CollectionName, FOnCreateCollectionSuccess OnSuccess, FOnCreateCollectionFailed OnFailed)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(FString::Printf(TEXT("%s/api/v1/collections"), *BaseUrl));
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    JsonObject->SetStringField(TEXT("name"), CollectionName);
    JsonObject->SetBoolField(TEXT("get_or_create"), true);
    FString RequestBody;
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<TCHAR>::Create(&RequestBody));
    HttpRequest->SetContentAsString(RequestBody);
    HttpRequest->OnProcessRequestComplete().BindSP(this, &FChromaDBClient::OnCreateCollectionResponse, OnSuccess, OnFailed);
    HttpRequest->ProcessRequest();
}

// ⭐️ 시그니처가 FOnAddEmbeddingsSuccess, FOnAddEmbeddingsFailed 로 변경!
void FChromaDBClient::AddEmbeddings(const FString& CollectionID, const TArray<FRAGIndexedChunk>& Chunks, FOnAddEmbeddingsSuccess OnSuccess, FOnAddEmbeddingsFailed OnFailed)
{
    if (Chunks.Num() == 0) { OnSuccess.ExecuteIfBound(TEXT("No chunks to add.")); return; }
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(FString::Printf(TEXT("%s/api/v1/collections/%s/add"), *BaseUrl, *CollectionID));
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> EmbeddingsArray, DocumentsArray, IdsArray;
    for (int32 i = 0; i < Chunks.Num(); ++i) {
        TArray<TSharedPtr<FJsonValue>> VectorArray;
        for (const float& Val : Chunks[i].EmbeddingVector) { VectorArray.Add(MakeShared<FJsonValueNumber>(Val)); }
        EmbeddingsArray.Add(MakeShared<FJsonValueArray>(VectorArray));
        DocumentsArray.Add(MakeShared<FJsonValueString>(Chunks[i].ChunkText));
        FString UniqueId = FString::Printf(TEXT("chunk_%s_%d"), *FGuid::NewGuid().ToString(), i);
        IdsArray.Add(MakeShared<FJsonValueString>(UniqueId));
    }
    JsonObject->SetArrayField(TEXT("embeddings"), EmbeddingsArray);
    JsonObject->SetArrayField(TEXT("documents"), DocumentsArray);
    JsonObject->SetArrayField(TEXT("ids"), IdsArray);
    FString RequestBody;
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<TCHAR>::Create(&RequestBody));
    HttpRequest->SetContentAsString(RequestBody);
    HttpRequest->OnProcessRequestComplete().BindSP(this, &FChromaDBClient::OnAddEmbeddingsResponse, OnSuccess, OnFailed);
    HttpRequest->ProcessRequest();
}

// ⭐️ 시그니처가 FOnQuerySuccess, FOnQueryFailed 로 변경!
void FChromaDBClient::QueryCollection(const FString& CollectionID, const TArray<float>& QueryEmbedding, int32 NumResults, FOnQuerySuccess OnSuccess, FOnQueryFailed OnFailed)
{
    if (QueryEmbedding.Num() == 0) { OnFailed.ExecuteIfBound(TEXT("Query embedding vector is empty.")); return; }
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(FString::Printf(TEXT("%s/api/v1/collections/%s/query"), *BaseUrl, *CollectionID));
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> QueryEmbeddingsArray;
    TArray<TSharedPtr<FJsonValue>> VectorArray;
    for (const float& Val : QueryEmbedding) { VectorArray.Add(MakeShared<FJsonValueNumber>(Val)); }
    QueryEmbeddingsArray.Add(MakeShared<FJsonValueArray>(VectorArray));
    JsonObject->SetArrayField(TEXT("query_embeddings"), QueryEmbeddingsArray);
    JsonObject->SetNumberField(TEXT("n_results"), NumResults);
    TArray<TSharedPtr<FJsonValue>> IncludeArray;
    IncludeArray.Add(MakeShared<FJsonValueString>(TEXT("documents")));
    JsonObject->SetArrayField(TEXT("include"), IncludeArray);
    FString RequestBody;
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<TCHAR>::Create(&RequestBody));
    HttpRequest->SetContentAsString(RequestBody);
    HttpRequest->OnProcessRequestComplete().BindSP(this, &FChromaDBClient::OnQueryCollectionResponse, OnSuccess, OnFailed);
    HttpRequest->ProcessRequest();
}

// ⭐️ 콜백 시그니처도 헤더와 동일하게 변경!
void FChromaDBClient::OnCreateCollectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnCreateCollectionSuccess OnSuccess, FOnCreateCollectionFailed OnFailed)
{
    if (bWasSuccessful && Response.IsValid() && Response->GetResponseCode() == 200) {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
        if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
            FChromaCollectionInfo CollectionInfo;
            JsonObject->TryGetStringField(TEXT("id"), CollectionInfo.ID);
            JsonObject->TryGetStringField(TEXT("name"), CollectionInfo.Name);
            if (!CollectionInfo.ID.IsEmpty()) {
                OnSuccess.ExecuteIfBound(CollectionInfo);
                return;
            }
        }
    }
    FString ErrorMessage = TEXT("Failed to create or get ChromaDB collection.");
    if (Response.IsValid()) { ErrorMessage += FString::Printf(TEXT(" Response Code: %d, Body: %s"), Response->GetResponseCode(), *Response->GetContentAsString()); }
    OnFailed.ExecuteIfBound(ErrorMessage);
}

// ⭐️ 콜백 시그니처도 헤더와 동일하게 변경!
void FChromaDBClient::OnAddEmbeddingsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnAddEmbeddingsSuccess OnSuccess, FOnAddEmbeddingsFailed OnFailed)
{
    if (bWasSuccessful && Response.IsValid() && (Response->GetResponseCode() == 200 || Response->GetResponseCode() == 201)) {
        OnSuccess.ExecuteIfBound(Response->GetContentAsString());
    }
    else {
        FString ErrorMessage = TEXT("Failed to add embeddings to ChromaDB.");
        if (Response.IsValid()) { ErrorMessage += FString::Printf(TEXT(" Response Code: %d, Body: %s"), Response->GetResponseCode(), *Response->GetContentAsString()); }
        OnFailed.ExecuteIfBound(ErrorMessage);
    }
}

// ⭐️ 콜백 시그니처도 헤더와 동일하게 변경!
void FChromaDBClient::OnQueryCollectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnQuerySuccess OnSuccess, FOnQueryFailed OnFailed)
{
    if (bWasSuccessful && Response.IsValid() && Response->GetResponseCode() == 200) {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
        if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
            const TArray<TSharedPtr<FJsonValue>>* DocumentsArrayOuter;
            if (JsonObject->TryGetArrayField(TEXT("documents"), DocumentsArrayOuter) && DocumentsArrayOuter->Num() > 0) {
                const TArray<TSharedPtr<FJsonValue>>* DocumentsArrayInner = nullptr;
                if ((*DocumentsArrayOuter)[0]->TryGetArray(DocumentsArrayInner)) {
                    TArray<FString> RetrievedDocs;
                    for (const TSharedPtr<FJsonValue>& DocValue : *DocumentsArrayInner) {
                        RetrievedDocs.Add(DocValue->AsString());
                    }
                    OnSuccess.ExecuteIfBound(RetrievedDocs);
                    return;
                }
            }
        }
    }
    FString ErrorMessage = TEXT("Failed to query or parse response from ChromaDB.");
    if (Response.IsValid()) { ErrorMessage += FString::Printf(TEXT(" Response Code: %d, Body: %s"), Response->GetResponseCode(), *Response->GetContentAsString()); }
    OnFailed.ExecuteIfBound(ErrorMessage);
}