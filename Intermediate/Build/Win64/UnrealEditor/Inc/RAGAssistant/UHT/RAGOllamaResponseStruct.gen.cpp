// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RAGAssistant/Public/Models/Ollama/RAGOllamaResponseStruct.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRAGOllamaResponseStruct() {}

// Begin Cross Module References
RAGASSISTANT_API UScriptStruct* Z_Construct_UScriptStruct_FRAGResponse();
RAGASSISTANT_API UScriptStruct* Z_Construct_UScriptStruct_FRAGResponseMessage();
UPackage* Z_Construct_UPackage__Script_RAGAssistant();
// End Cross Module References

// Begin ScriptStruct FRAGResponseMessage
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RAGResponseMessage;
class UScriptStruct* FRAGResponseMessage::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RAGResponseMessage.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RAGResponseMessage.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRAGResponseMessage, (UObject*)Z_Construct_UPackage__Script_RAGAssistant(), TEXT("RAGResponseMessage"));
	}
	return Z_Registration_Info_UScriptStruct_RAGResponseMessage.OuterSingleton;
}
template<> RAGASSISTANT_API UScriptStruct* StaticStruct<FRAGResponseMessage>()
{
	return FRAGResponseMessage::StaticStruct();
}
struct Z_Construct_UScriptStruct_FRAGResponseMessage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// chat API\xec\x9d\x98 \xec\x9d\x91\xeb\x8b\xb5 \xeb\xa9\x94\xec\x8b\x9c\xec\xa7\x80 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "chat API\xec\x9d\x98 \xec\x9d\x91\xeb\x8b\xb5 \xeb\xa9\x94\xec\x8b\x9c\xec\xa7\x80 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Content_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Role;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Content;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRAGResponseMessage>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGResponseMessage, Role), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::NewProp_Content = { "Content", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGResponseMessage, Content), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Content_MetaData), NewProp_Content_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::NewProp_Content,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_RAGAssistant,
	nullptr,
	&NewStructOps,
	"RAGResponseMessage",
	Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::PropPointers),
	sizeof(FRAGResponseMessage),
	alignof(FRAGResponseMessage),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FRAGResponseMessage()
{
	if (!Z_Registration_Info_UScriptStruct_RAGResponseMessage.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RAGResponseMessage.InnerSingleton, Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_RAGResponseMessage.InnerSingleton;
}
// End ScriptStruct FRAGResponseMessage

// Begin ScriptStruct FRAGResponse
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RAGResponse;
class UScriptStruct* FRAGResponse::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RAGResponse.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RAGResponse.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRAGResponse, (UObject*)Z_Construct_UPackage__Script_RAGAssistant(), TEXT("RAGResponse"));
	}
	return Z_Registration_Info_UScriptStruct_RAGResponse.OuterSingleton;
}
template<> RAGASSISTANT_API UScriptStruct* StaticStruct<FRAGResponse>()
{
	return FRAGResponse::StaticStruct();
}
struct Z_Construct_UScriptStruct_FRAGResponse_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xa9\x94\xec\x9d\xb8 \xec\x9d\x91\xeb\x8b\xb5 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xa9\x94\xec\x9d\xb8 \xec\x9d\x91\xeb\x8b\xb5 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Response_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// generate API\xec\x9d\x98 \xec\x9d\x91\xeb\x8b\xb5\n" },
#endif
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "generate API\xec\x9d\x98 \xec\x9d\x91\xeb\x8b\xb5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// chat API\xec\x9d\x98 \xec\x9d\x91\xeb\x8b\xb5\n" },
#endif
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "chat API\xec\x9d\x98 \xec\x9d\x91\xeb\x8b\xb5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Model_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CreatedAt_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDone_MetaData[] = {
		{ "ModuleRelativePath", "Public/Models/Ollama/RAGOllamaResponseStruct.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Response;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Message;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Model;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CreatedAt;
	static void NewProp_bDone_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDone;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRAGResponse>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGResponse, Response), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Response_MetaData), NewProp_Response_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGResponse, Message), Z_Construct_UScriptStruct_FRAGResponseMessage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) }; // 173164058
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_Model = { "Model", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGResponse, Model), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Model_MetaData), NewProp_Model_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_CreatedAt = { "CreatedAt", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FRAGResponse, CreatedAt), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CreatedAt_MetaData), NewProp_CreatedAt_MetaData) };
void Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_bDone_SetBit(void* Obj)
{
	((FRAGResponse*)Obj)->bDone = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_bDone = { "bDone", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FRAGResponse), &Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_bDone_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDone_MetaData), NewProp_bDone_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRAGResponse_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_Response,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_Message,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_Model,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_CreatedAt,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRAGResponse_Statics::NewProp_bDone,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGResponse_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRAGResponse_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_RAGAssistant,
	nullptr,
	&NewStructOps,
	"RAGResponse",
	Z_Construct_UScriptStruct_FRAGResponse_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGResponse_Statics::PropPointers),
	sizeof(FRAGResponse),
	alignof(FRAGResponse),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRAGResponse_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FRAGResponse_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FRAGResponse()
{
	if (!Z_Registration_Info_UScriptStruct_RAGResponse.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RAGResponse.InnerSingleton, Z_Construct_UScriptStruct_FRAGResponse_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_RAGResponse.InnerSingleton;
}
// End ScriptStruct FRAGResponse

// Begin Registration
struct Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaResponseStruct_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FRAGResponseMessage::StaticStruct, Z_Construct_UScriptStruct_FRAGResponseMessage_Statics::NewStructOps, TEXT("RAGResponseMessage"), &Z_Registration_Info_UScriptStruct_RAGResponseMessage, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRAGResponseMessage), 173164058U) },
		{ FRAGResponse::StaticStruct, Z_Construct_UScriptStruct_FRAGResponse_Statics::NewStructOps, TEXT("RAGResponse"), &Z_Registration_Info_UScriptStruct_RAGResponse, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRAGResponse), 1119781550U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaResponseStruct_h_1640436939(TEXT("/Script/RAGAssistant"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaResponseStruct_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Models_Ollama_RAGOllamaResponseStruct_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
