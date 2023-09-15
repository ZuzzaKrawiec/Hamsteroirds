// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MenuManager/ZZMenuManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menu/ZZMenuBaseWidget.h"
#include "GameMode/ZZPlayerController.h"
#include "Settings/ZZUISettings.h"
#include "GameMode/ZZPawn.h"

UZZMenuManagerComponent::UZZMenuManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UZZMenuManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	AZZPlayerController* PlayerController = Cast<AZZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->OnGamePawnSpawned.AddDynamic(this, &UZZMenuManagerComponent::OnGamePawnSpawned);
	}
}

void UZZMenuManagerComponent::OpenMenuDelegate(UZZMenuBaseWidget* InMenu, TSoftClassPtr<UZZMenuBaseWidget> InMenuWidgetClass)
{
	CloseMenu(InMenu);
	OpenMenu(InMenuWidgetClass);
}

void UZZMenuManagerComponent::OpenMenu(TSoftClassPtr<UZZMenuBaseWidget> InMenuWidgetClass, bool bOverlay)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UZZMenuManagerComponent::OpenMenu no player controller"))
			return;
	}

	if (InMenuWidgetClass.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("UZZMenuManagerComponent::OpenMenu InMenuWidgetClass is null"))
			return;
	}
	if (PlayerController->GetPawn())
	{
		AZZPawn* Pawn = Cast<AZZPawn>(PlayerController->GetPawn());
		if (Pawn)
		{
			Pawn->SetLockInteraction(!bOverlay);
		}
	}
	TSubclassOf<UZZMenuBaseWidget> MenuWidgetClass = InMenuWidgetClass.LoadSynchronous();
	UZZMenuBaseWidget* NewMenu = Cast<UZZMenuBaseWidget>(CreateWidget(PlayerController, MenuWidgetClass));
	if (!NewMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("UZZMenuManagerComponent::OpenMenu widget not created"))
		return;
	}
	NewMenu->OnCloseMenu.AddUObject(this, &UZZMenuManagerComponent::CloseMenu);
	NewMenu->OnOpenMenu.AddUObject(this, &UZZMenuManagerComponent::OpenMenuDelegate);
	NewMenu->AddToViewport(0);
	if (!bOverlay)
	{
		CurrentOpenedMenuWidget = NewMenu;
	}
}
void UZZMenuManagerComponent::CloseMenu(UZZMenuBaseWidget* InMenu)
{
	if (!InMenu)
	{
		return;
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UZZMenuManagerComponent::OpenMenu no player controller"))
		return;
	}

	if (PlayerController->GetPawn())
	{
		AZZPawn* Pawn = Cast<AZZPawn>(PlayerController->GetPawn());
		if (Pawn)
		{
			Pawn->SetLockInteraction(false);
		}
	}
	if (CurrentOpenedMenuWidget == InMenu)
	{
		CurrentOpenedMenuWidget = nullptr;
	}
	CurrentMenuType = EMenuType::None;
	InMenu->ClearDelegates();
	InMenu->RemoveFromParent();
}
void UZZMenuManagerComponent::OnGamePawnSpawned(AZZPawn* InPawn)
{
	if (!InPawn)
	{
		return;
	}
	InPawn->OnOpenMenuInteraction.AddDynamic(this, &UZZMenuManagerComponent::OpenMenuInteration);
}
void UZZMenuManagerComponent::OpenMenuInteration(EMenuType InMenuType)
{
	OpenMenuByEnum(InMenuType);
}
void UZZMenuManagerComponent::OpenMenuByEnum(EMenuType InMenuType, bool bOverlay)
{
	if (CurrentMenuType == InMenuType)
	{
		CloseMenu(CurrentOpenedMenuWidget);
	}
	else
	{
		CloseMenu(CurrentOpenedMenuWidget);
		OpenMenu(*GetDefault<UZZUISettings>()->MenuWidgetClass.Find(InMenuType), bOverlay);
		CurrentMenuType = InMenuType;
	}
}