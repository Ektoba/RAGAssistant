// FRAGFileUtils.cpp

#include "FRAGFileUtils.h"
#include "HAL/FileManager.h" // IFileManager를 사용하기 위해 필요!
#include "Misc/FileHelper.h"

bool FRAGFileUtils::FindProjectFiles(const FString& RootDir, TArray<FString>& OutFilePaths, const TArray<FString>& Extensions)
{
    if (RootDir.IsEmpty() || Extensions.Num() == 0)
    {
        return false;
    }

    // 파일 매니저 인스턴스를 가져온다.
    IFileManager& FileManager = IFileManager::Get();

    // 1. 경로를 표준 형식으로 정리합니다. (예: "C:/MyFolder/" 처럼)
    FString NormalizedRootDir = RootDir;
    FPaths::NormalizeDirectoryName(NormalizedRootDir);

    UE_LOG(LogTemp, Log, TEXT("FRAGFileUtils: Starting search in normalized root: %s"), *NormalizedRootDir);

    int32 TotalFoundInThisCall = 0;

    // 2. 각 확장자에 대해 개별적으로 검색하고 로그를 남깁니다.
    for (const FString& Ext : Extensions)
    {
        TArray<FString> FoundThisIteration;
        FileManager.FindFilesRecursive(FoundThisIteration, *NormalizedRootDir, *Ext, true, false);

        int32 NumFound = FoundThisIteration.Num();
        if (NumFound > 0)
        {
            // 찾은 파일이 있을 경우에만 로그를 남겨서 로그 창을 깔끔하게 유지합니다.
            UE_LOG(LogTemp, Log, TEXT("FRAGFileUtils: Found %d files with extension '%s' in %s"), NumFound, *Ext, *NormalizedRootDir);
            OutFilePaths.Append(FoundThisIteration);
            TotalFoundInThisCall += NumFound;
        }
    }

    UE_LOG(LogTemp, Log, TEXT("FRAGFileUtils: Finished search. Total files appended in this call: %d"), TotalFoundInThisCall);

    return TotalFoundInThisCall > 0;
}

TArray<FString> FRAGFileUtils::ChunkFileContent(const FString& FileContent, int32 ChunkSizeLines, int32 OverlapLines)
{
    TArray<FString> Chunks;
    TArray<FString> Lines;

    // 전체 내용을 줄 단위로 나눔
    FileContent.ParseIntoArrayLines(Lines);

    if (Lines.Num() == 0)
    {
        return Chunks;
    }

    int32 CurrentLine = 0;
    while (CurrentLine < Lines.Num())
    {
        int32 StartLine = CurrentLine;
        int32 EndLine = FMath::Min(StartLine + ChunkSizeLines, Lines.Num());

        TArray<FString> ChunkLines;
        for (int32 i = StartLine; i < EndLine; ++i)
        {
            ChunkLines.Add(Lines[i]);
        }

        Chunks.Add(FString::Join(ChunkLines, TEXT("\n")));

        CurrentLine += (ChunkSizeLines - OverlapLines);
        if (ChunkSizeLines - OverlapLines <= 0)
        {
            CurrentLine++;
        }
    }

    return Chunks;
}