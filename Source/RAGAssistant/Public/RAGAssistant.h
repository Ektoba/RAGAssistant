// RAGAssistant.h (최종 수정본)

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FExtender;
class SDockTab;
class FSpawnTabArgs;

class FRAGAssistantModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void OnMenuButtonClicked();
	TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<FExtender> MenuExtender;
};