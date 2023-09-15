// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Main/ZZMainMenuWidget.h"
#include "Settings/ZZUISettings.h"
#include "GameMode/ZZGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UZZMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonStartGame->OnButtonPressed.AddDynamic(this, &UZZMainMenuWidget::StartGame);
	ButtonSettings->OnButtonPressed.AddDynamic(this, &UZZMainMenuWidget::OpenSettings);
	ButtonQuit->OnButtonPressed.AddDynamic(this, &UZZMainMenuWidget::QuitButton);
}
void UZZMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}
void UZZMainMenuWidget::StartGame(UZZButtonBaseWidget* InButton)
{	
	AZZGameState* GameState = Cast<AZZGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState)
	{
		return;
	}
	ButtonStartGame->SetIsEnabled(false);
	ButtonSettings->SetIsEnabled(false);
	FOnStartWorldLoaded OnStartWorldLoaded;
	OnStartWorldLoaded.BindLambda([=] {
		OnCloseMenu.Broadcast(this);
	});
	GameState->StartGame(OnStartWorldLoaded);
}
void UZZMainMenuWidget::OpenSettings(UZZButtonBaseWidget* InButton)
{

}
void UZZMainMenuWidget::QuitButton(UZZButtonBaseWidget* InButton)
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
