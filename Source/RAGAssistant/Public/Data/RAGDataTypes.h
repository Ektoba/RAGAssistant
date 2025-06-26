#pragma once

#include "CoreMinimal.h"
#include "RAGDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FRAGIndexedChunk
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString ChunkText;

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    TArray<float> EmbeddingVector;

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString ChunkID; // added new property to store unique identifier

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString AdditionalInfo; // added new property for extra information

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString CreatedTimestamp; // added new property to store creation date and time

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString UpdatedTimestamp; // added new property to store last update date and time

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString ChunkDescription; // added new property for chunk description

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString Metadata; // added new property for additional metadata

    UPROPERTY(BlueprintReadOnly, Category = "RAG")
    FString Author; // added new property for the author's name
};

USTRUCT(BlueprintType)
struct FChromaCollectionInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "ChromaDB")
    FString Name;

    UPROPERTY(BlueprintReadOnly, Category = "ChromaDB")
    FString ID; // 컬렉션의 고유 UUID
};