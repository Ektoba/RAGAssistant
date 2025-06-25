// RAGAssistant.cpp (최종 수정본)

#include "RAGAssistant.h"
#include "Widget/RAGChatWidget.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName RAGAssistantTabName("RAGAssistant");

IMPLEMENT_MODULE(FRAGAssistantModule, RAGAssistant)

void FRAGAssistantModule::StartupModule()
{
	MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuBarExtension(
		"Window",
		EExtensionHook::After,
		nullptr, // ⭐️ CommandList가 필요 없으므로 nullptr!
		FMenuBarExtensionDelegate::CreateLambda([this](FMenuBarBuilder& BarBuilder)
			{
				BarBuilder.AddMenuEntry(
					FText::FromString("RAG Assistant"),
					FText::FromString("Open the RAG Assistant chat window"),
					FSlateIcon(),
					// ⭐️ 여기에 FUIAction을 바로 생성해서 넣어주면 돼!
					FUIAction(FExecuteAction::CreateRaw(this, &FRAGAssistantModule::OnMenuButtonClicked))
				);
			})
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	FGlobalTabmanager::Get()->RegisterTabSpawner(RAGAssistantTabName, FOnSpawnTab::CreateRaw(this, &FRAGAssistantModule::OnSpawnPluginTab))
		.SetDisplayName(FText::FromString("RAG Assistant"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FRAGAssistantModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterTabSpawner(RAGAssistantTabName);

	if (MenuExtender.IsValid() && FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorModule.GetMenuExtensibilityManager()->RemoveExtender(MenuExtender);
	}
}

TSharedRef<SDockTab> FRAGAssistantModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SRagChatWidget)
		];
}

void FRAGAssistantModule::OnMenuButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(RAGAssistantTabName);
}