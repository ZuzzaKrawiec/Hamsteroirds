// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ZZGameState.h"
#include "Components/LevelStreamer/ZZLevelStreamerManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/ZZPlayerController.h"
#include "GameMode/ZZHUD.h"
#include "Settings/ZZUISettings.h"
#include "Settings/ZZSettings.h"
#include "UI/Menu/ZZMenuBaseWidget.h"
#include "Components/MenuManager/ZZMenuManagerComponent.h"
#include "Components/LevelStreamer/ZZLevelStreamerManagerComponent.h"
#include "Components/LocationMark/ZZLocationMarkManagerComponent.h"


AZZGameState::AZZGameState()
{
	LevelStreamerManagerComponent = CreateDefaultSubobject<UZZLevelStreamerManagerComponent>(FName("LevelStreamerManagerComponent"));
	LevelStreamerManagerComponent->bEditableWhenInherited = true;
	
	LocationMarkManagerComponent = CreateDefaultSubobject<UZZLocationMarkManagerComponent>(FName("LocationMarkManagerComponent"));
	LocationMarkManagerComponent->bEditableWhenInherited = true;
}


void AZZGameState::BeginPlay()
{
	Super::BeginPlay();
	StartMenu();
}
void AZZGameState::StartMenu()
{
	APlayerController* PlayerController =  Cast<AZZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController)
	{
		return;
	}
	AZZHUD* HUD = Cast<AZZHUD>(PlayerController->GetHUD());
	if (!HUD)
	{
		return;
	}

	UZZMenuManagerComponent* MenuManagerComponent = HUD->GetMenuManagerComponent();
	if (!MenuManagerComponent)
	{
		return;
	}
	MenuManagerComponent->OpenMenuByEnum(EMenuType::Main);
}
void AZZGameState::StartGame(FOnStartWorldLoaded InOnStartWorldLoaded)
{
	if (!LevelStreamerManagerComponent)
	{
		return;
	}
	OnStartWorldLoaded = InOnStartWorldLoaded;
	ULevelStreamingDynamic* StartLevel = LevelStreamerManagerComponent->AddStreamLevel(GetDefault<UZZSettings>()->WorldStart, 0, false);
	if(StartLevel)
	{ 
		StartLevel->OnLevelLoaded.AddDynamic(this, &AZZGameState::StartWorldLoaded);
	}	
}
void AZZGameState::StartWorldLoaded()
{
	OnStartWorldLoaded.ExecuteIfBound();
	FirstGameStart();
}

void AZZGameState::FirstGameStart()
{
	if (bGamePrepared)
	{
		return;
	}
	bGamePrepared = true;

	AZZPlayerController* PlayerController = Cast<AZZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController)
	{
		return;
	}
	AZZHUD* HUD = Cast<AZZHUD>(PlayerController->GetHUD());
	if (!HUD)
	{
		return;
	}
	UZZMenuManagerComponent* MenuManagerComponent = HUD->GetMenuManagerComponent();
	if (!MenuManagerComponent)
	{
		return;
	}
	MenuManagerComponent->OpenMenuByEnum(EMenuType::ChangeHamster);
	if (MenuManagerComponent->GetCurrentOpenedMenuWidget())
	{
		MenuManagerComponent->GetCurrentOpenedMenuWidget()->OnCloseMenu.AddLambda([=] (UZZMenuBaseWidget* InMenu){
			PlayerController->CreateGamePawn();
			LevelStreamerManagerComponent->StartEndlessStreaming();

			MenuManagerComponent->OpenMenuByEnum(EMenuType::Game, true);
		});
	}
}