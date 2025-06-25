// FRAGFileUtils.h

#pragma once

#include "CoreMinimal.h"

/**
 * @brief RAG 시스템에 필요한 파일 관련 유틸리티 함수들을 모아둔 클래스
 */
class RAGASSISTANT_API FRAGFileUtils
{
public:
    /**
     * 지정된 디렉토리와 그 하위 디렉토리에서 특정 확장자를 가진 모든 파일의 경로를 찾습니다.
     * @param RootDir 검색을 시작할 최상위 디렉토리 경로
     * @param OutFilePaths 찾은 파일들의 전체 경로가 저장될 배열
     * @param Extensions 찾고자 하는 파일 확장자 배열 (예: { "*.h", "*.cpp" })
     * @return 파일을 하나 이상 찾았으면 true, 아니면 false를 반환합니다.
     */
    static bool FindProjectFiles(const FString& RootDir, TArray<FString>& OutFilePaths, const TArray<FString>& Extensions);
    static TArray<FString> ChunkFileContent(const FString& FileContent, int32 ChunkSizeLines, int32 OverlapLines);
};