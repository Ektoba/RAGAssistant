// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RAGAssistant/Public/Models/Ollama/RAGOllamaRequestStruct.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRAGOllamaRequestStruct() {}

// Begin Cross Module References
RAGASSISTANT_API UScriptStruct* Z_Construct_UScriptStruct_FRAGChatMessage();
RAGASSISTANT_API UScriptStruct* Z_Construct_UScriptStruct_FRAGRequest();
UPackage* Z_Construct_UPackage__Script_RAGAssistant();
// End Cross Module References

// Begin ScriptStruct FRAGChatMessage
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RAGChatMessage;
class UScriptStruct* FRAGChatMessage::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RAGChatMessage.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RAGChatMessage.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRAGChatMessage, (UObject*)Z_Construct_UPackage__Script_RAGAssistant(), TEXT("RAGChatMessage"));
	}
	return Z_Registration_Info_UScriptStruct_RAGChatMessage.OuterSingleton;
}
template<> RAGASSISTANT_API UScriptStruct* StaticStruct<FRAGChatMessage>()
{
	return FRAGChatMessage::StaticStruct();
}
struct Z_Construct_UScriptStruct_FRAGChatMessage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Content_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \"system\", \"user\", \"assistant\"\n" },
#endif
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\"system\", \"user\", \"assistant\"" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Role;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Content;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRAGChatMessage>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGChatMessage_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGChatMessage, Role), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGChatMessage_Statics::NewProp_Content = { "Content", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGChatMessage, Content), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Content_MetaData), NewProp_Content_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRAGChatMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGChatMessage_Statics::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGChatMessage_Statics::NewProp_Content,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGChatMessage_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRAGChatMessage_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_RAGAssistant,
	nullptr,
	&NewStructOps,
	"RAGChatMessage",
	Z_Construct_UScriptStruct_FRAGChatMessage_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGChatMessage_Statics::PropPointers),
	sizeof(FRAGChatMessage),
	alignof(FRAGChatMessage),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGChatMessage_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRAGChatMessage_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FRAGChatMessage()
{
	if (!Z_Registration_Info_UScriptStruct_RAGChatMessage.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RAGChatMessage.InnerSingleton, Z_Construct_UScriptStruct_FRAGChatMessage_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_RAGChatMessage.InnerSingleton;
}
// End ScriptStruct FRAGChatMessage

// Begin ScriptStruct FRAGRequest
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RAGRequest;
class UScriptStruct* FRAGRequest::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RAGRequest.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RAGRequest.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRAGRequest, (UObject*)Z_Construct_UPackage__Script_RAGAssistant(), TEXT("RAGRequest"));
	}
	return Z_Registration_Info_UScriptStruct_RAGRequest.OuterSingleton;
}
template<> RAGASSISTANT_API UScriptStruct* StaticStruct<FRAGRequest>()
{
	return FRAGRequest::StaticStruct();
}
struct Z_Construct_UScriptStruct_FRAGRequest_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Model_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Prompt_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 'generate' API\xeb\xa5\xbc \xec\x9c\x84\xed\x95\x9c \xeb\x8b\xa8\xec\x9d\xbc \xed\x94\x84\xeb\xa1\xac\xed\x94\x84\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "'generate' API\xeb\xa5\xbc \xec\x9c\x84\xed\x95\x9c \xeb\x8b\xa8\xec\x9d\xbc \xed\x94\x84\xeb\xa1\xac\xed\x94\x84\xed\x8a\xb8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Messages_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 'chat' API\xeb\xa5\xbc \xec\x9c\x84\xed\x95\x9c \xeb\xa9\x94\xec\x8b\x9c\xec\xa7\x80 \xeb\xb0\xb0\xec\x97\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "'chat' API\xeb\xa5\xbc \xec\x9c\x84\xed\x95\x9c \xeb\xa9\x94\xec\x8b\x9c\xec\xa7\x80 \xeb\xb0\xb0\xec\x97\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bStream_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaRequestStruct.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Model;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Prompt;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Messages_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Messages;
	static void NewProp_bStream_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bStream;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRAGRequest>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Model = { "Model", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGRequest, Model), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Model_MetaData), NewProp_Model_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Prompt = { "Prompt", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGRequest, Prompt), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Prompt_MetaData), NewProp_Prompt_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Messages_Inner = { "Messages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FRAGChatMessage, METADATA_PARAMS(0, nullptr) }; // 3223171116
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Messages = { "Messages", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGRequest, Messages), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Messages_MetaData), NewProp_Messages_MetaData) }; // 3223171116
void Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_bStream_SetBit(void* Obj)
{
	((FRAGRequest*)Obj)->bStream = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_bStream = { "bStream", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FRAGRequest), &Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_bStream_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bStream_MetaData), NewProp_bStream_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRAGRequest_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Model,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Prompt,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Messages_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_Messages,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGRequest_Statics::NewProp_bStream,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGRequest_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRAGRequest_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_RAGAssistant,
	nullptr,
	&NewStructOps,
	"RAGRequest",
	Z_Construct_UScriptStruct_FRAGRequest_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGRequest_Statics::PropPointers),
	sizeof(FRAGRequest),
	alignof(FRAGRequest),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGRequest_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRAGRequest_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FRAGRequest()
{
	if (!Z_Registration_Info_UScriptStruct_RAGRequest.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RAGRequest.InnerSingleton, Z_Construct_UScriptStruct_FRAGRequest_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_RAGRequest.InnerSingleton;
}
// End ScriptStruct FRAGRequest

// Begin Registration
struct Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaRequestStruct_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FRAGChatMessage::StaticStruct, Z_Construct_UScriptStruct_FRAGChatMessage_Statics::NewStructOps, TEXT("RAGChatMessage"), &Z_Registration_Info_UScriptStruct_RAGChatMessage, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRAGChatMessage), 3223171116U) },
		{ FRAGRequest::StaticStruct, Z_Construct_UScriptStruct_FRAGRequest_Statics::NewStructOps, TEXT("RAGRequest"), &Z_Registration_Info_UScriptStruct_RAGRequest, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRAGRequest), 1455002150U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaRequestStruct_h_2179694105(TEXT("/Script/RAGAssistant"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaRequestStruct_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaRequestStruct_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
