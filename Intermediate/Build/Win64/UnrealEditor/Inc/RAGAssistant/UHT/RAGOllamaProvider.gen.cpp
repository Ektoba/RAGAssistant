// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RAGAssistant/Public/Provider/RAGOllamaProvider.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRAGOllamaProvider() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
RAGASSISTANT_API UClass* Z_Construct_UClass_URAGOllamaProvider();
RAGASSISTANT_API UClass* Z_Construct_UClass_URAGOllamaProvider_NoRegister();
UPackage* Z_Construct_UPackage__Script_RAGAssistant();
// End Cross Module References

// Begin Class URAGOllamaProvider Function InitOllamaProvider
struct Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics
{
	struct RAGOllamaProvider_eventInitOllamaProvider_Parms
	{
		FString InOllamaServerUrl;
		FString InDefaultOllamaModel;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Ollama Settings" },
		{ "ModuleRelativePath", "Public/Provider/RAGOllamaProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InOllamaServerUrl_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InDefaultOllamaModel_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_InOllamaServerUrl;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InDefaultOllamaModel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::NewProp_InOllamaServerUrl = { "InOllamaServerUrl", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RAGOllamaProvider_eventInitOllamaProvider_Parms, InOllamaServerUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InOllamaServerUrl_MetaData), NewProp_InOllamaServerUrl_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::NewProp_InDefaultOllamaModel = { "InDefaultOllamaModel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RAGOllamaProvider_eventInitOllamaProvider_Parms, InDefaultOllamaModel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InDefaultOllamaModel_MetaData), NewProp_InDefaultOllamaModel_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::NewProp_InOllamaServerUrl,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::NewProp_InDefaultOllamaModel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URAGOllamaProvider, nullptr, "InitOllamaProvider", nullptr, nullptr, Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::PropPointers), sizeof(Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::RAGOllamaProvider_eventInitOllamaProvider_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::Function_MetaDataParams), Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::RAGOllamaProvider_eventInitOllamaProvider_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URAGOllamaProvider::execInitOllamaProvider)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_InOllamaServerUrl);
	P_GET_PROPERTY(FStrProperty,Z_Param_InDefaultOllamaModel);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitOllamaProvider(Z_Param_InOllamaServerUrl,Z_Param_InDefaultOllamaModel);
	P_NATIVE_END;
}
// End Class URAGOllamaProvider Function InitOllamaProvider

// Begin Class URAGOllamaProvider
void URAGOllamaProvider::StaticRegisterNativesURAGOllamaProvider()
{
	UClass* Class = URAGOllamaProvider::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "InitOllamaProvider", &URAGOllamaProvider::execInitOllamaProvider },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URAGOllamaProvider);
UClass* Z_Construct_UClass_URAGOllamaProvider_NoRegister()
{
	return URAGOllamaProvider::StaticClass();
}
struct Z_Construct_UClass_URAGOllamaProvider_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * @brief Ollama \xeb\xa1\x9c\xec\xbb\xac LLM\xea\xb3\xbc\xec\x9d\x98 \xed\x86\xb5\xec\x8b\xa0\xec\x9d\x84 \xeb\x8b\xb4\xeb\x8b\xb9\xed\x95\x98\xeb\x8a\x94 Generative AI Provider \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4\xec\x9e\x85\xeb\x8b\x88\xeb\x8b\xa4.\n * \xec\x9d\xb4 \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4\xeb\x8a\x94 \xea\xb8\xb0\xec\xa1\xb4 \xed\x94\x8c\xeb\x9f\xac\xea\xb7\xb8\xec\x9d\xb8\xec\x9d\x98 \xeb\x8b\xa4\xeb\xa5\xb8 Provider (\xec\x98\x88: OpenAI)\xec\x99\x80 \xec\x9c\xa0\xec\x82\xac\xed\x95\x9c \xeb\xb0\xa9\xec\x8b\x9d\xec\x9c\xbc\xeb\xa1\x9c \xea\xb5\xac\xed\x98\x84\xeb\x90\xa9\xeb\x8b\x88\xeb\x8b\xa4.\n */" },
#endif
		{ "IncludePath", "Provider/RAGOllamaProvider.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/Provider/RAGOllamaProvider.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "@brief Ollama \xeb\xa1\x9c\xec\xbb\xac LLM\xea\xb3\xbc\xec\x9d\x98 \xed\x86\xb5\xec\x8b\xa0\xec\x9d\x84 \xeb\x8b\xb4\xeb\x8b\xb9\xed\x95\x98\xeb\x8a\x94 Generative AI Provider \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4\xec\x9e\x85\xeb\x8b\x88\xeb\x8b\xa4.\n\xec\x9d\xb4 \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4\xeb\x8a\x94 \xea\xb8\xb0\xec\xa1\xb4 \xed\x94\x8c\xeb\x9f\xac\xea\xb7\xb8\xec\x9d\xb8\xec\x9d\x98 \xeb\x8b\xa4\xeb\xa5\xb8 Provider (\xec\x98\x88: OpenAI)\xec\x99\x80 \xec\x9c\xa0\xec\x82\xac\xed\x95\x9c \xeb\xb0\xa9\xec\x8b\x9d\xec\x9c\xbc\xeb\xa1\x9c \xea\xb5\xac\xed\x98\x84\xeb\x90\xa9\xeb\x8b\x88\xeb\x8b\xa4." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OllamaServerUrl_MetaData[] = {
		{ "Category", "Ollama Settings" },
		{ "ModuleRelativePath", "Public/Provider/RAGOllamaProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultOllamaModel_MetaData[] = {
		{ "Category", "Ollama Settings" },
		{ "ModuleRelativePath", "Public/Provider/RAGOllamaProvider.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_OllamaServerUrl;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultOllamaModel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URAGOllamaProvider_InitOllamaProvider, "InitOllamaProvider" }, // 2954535655
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URAGOllamaProvider>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URAGOllamaProvider_Statics::NewProp_OllamaServerUrl = { "OllamaServerUrl", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URAGOllamaProvider, OllamaServerUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OllamaServerUrl_MetaData), NewProp_OllamaServerUrl_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URAGOllamaProvider_Statics::NewProp_DefaultOllamaModel = { "DefaultOllamaModel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URAGOllamaProvider, DefaultOllamaModel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultOllamaModel_MetaData), NewProp_DefaultOllamaModel_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URAGOllamaProvider_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URAGOllamaProvider_Statics::NewProp_OllamaServerUrl,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URAGOllamaProvider_Statics::NewProp_DefaultOllamaModel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URAGOllamaProvider_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_URAGOllamaProvider_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_RAGAssistant,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URAGOllamaProvider_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URAGOllamaProvider_Statics::ClassParams = {
	&URAGOllamaProvider::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URAGOllamaProvider_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URAGOllamaProvider_Statics::PropPointers),
	0,
	0x001000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URAGOllamaProvider_Statics::Class_MetaDataParams), Z_Construct_UClass_URAGOllamaProvider_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URAGOllamaProvider()
{
	if (!Z_Registration_Info_UClass_URAGOllamaProvider.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URAGOllamaProvider.OuterSingleton, Z_Construct_UClass_URAGOllamaProvider_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URAGOllamaProvider.OuterSingleton;
}
template<> RAGASSISTANT_API UClass* StaticClass<URAGOllamaProvider>()
{
	return URAGOllamaProvider::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(URAGOllamaProvider);
URAGOllamaProvider::~URAGOllamaProvider() {}
// End Class URAGOllamaProvider

// Begin Registration
struct Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Provider_RAGOllamaProvider_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URAGOllamaProvider, URAGOllamaProvider::StaticClass, TEXT("URAGOllamaProvider"), &Z_Registration_Info_UClass_URAGOllamaProvider, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URAGOllamaProvider), 492564106U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Provider_RAGOllamaProvider_h_315722565(TEXT("/Script/RAGAssistant"),
	Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Provider_RAGOllamaProvider_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SpartaTeamPrj_Final_1st_Team4_Final_Project_Plugins_RAGAssistant_Source_RAGAssistant_Public_Provider_RAGOllamaProvider_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
