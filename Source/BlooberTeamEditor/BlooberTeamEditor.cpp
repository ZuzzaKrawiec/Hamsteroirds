// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlooberTeamEditor.h"
#include "Modules/ModuleManager.h"
#include "TextStylePicker/ZZTextStylePicker.h"

DEFINE_LOG_CATEGORY(BlooberTeamEditor)
IMPLEMENT_GAME_MODULE(FBlooberTeamEditorModule, BlooberTeamEditor);

#define LOCTEXT_NAMESPACE "BlooberTeamEditorModule"

void FBlooberTeamEditorModule::StartupModule()
{
    UE_LOG(BlooberTeamEditor, Warning, TEXT("BlooberTeamEditorModule: Log Started"));
    RegisterCustomizations();
}

void FBlooberTeamEditorModule::ShutdownModule()
{
    UE_LOG(BlooberTeamEditor, Warning, TEXT("BlooberTeamEditorModule: Log Ended"));
}
void FBlooberTeamEditorModule::RegisterCustomizations()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.RegisterCustomPropertyTypeLayout("TextStylePicker", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FZZTextStylePicker::MakeInstance));
}
#undef LOCTEXT_NAMESPACE