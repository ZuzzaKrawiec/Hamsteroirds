// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Character/ZZCharacterMenuWidget.h"
#include "Settings/ZZUISettings.h"
#include "GameMode/ZZPlayerState.h"
#include "GameMode/ZZPawn.h"
#include "GameMode/ZZGameState.h"
#include "Kismet/GameplayStatics.h"


void UZZCharacterMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Hamster1)
	{
		Hamster1->OnCharacterSelected.BindUObject(this, &UZZCharacterMenuWidget::OnCharacterSelected);
	}
	if (Hamster2)
	{
		Hamster2->OnCharacterSelected.BindUObject(this, &UZZCharacterMenuWidget::OnCharacterSelected);
	}
	if (Hamster3)
	{
		Hamster3->OnCharacterSelected.BindUObject(this, &UZZCharacterMenuWidget::OnCharacterSelected);
	}



	if (ButtonClose)
	{
		AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
		if (!PlayerState)
		{
			return;
		}
		if (!PlayerState->GetHamsterData())
		{
			ButtonClose->SetVisibility(ESlateVisibility::Collapsed);
			return;
		}
		ButtonClose->OnButtonPressed.AddDynamic(this, &UZZCharacterMenuWidget::Close);
	}
}
void UZZCharacterMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}
void UZZCharacterMenuWidget::OnCharacterSelected(UZZCharacterDetailsWidget* InCharacterDetailsWidget)
{
	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if(!PlayerState)
	{
		return;
	}
	AZZGameState* GameState = Cast<AZZGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState)
	{
		return;
	}
	PlayerState->SetHamsterData(InCharacterDetailsWidget->GetHamsterData());
	

	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn)
	{
		Pawn->SpawnHamster();
	}

	OnCloseMenu.Broadcast(this);
}
void UZZCharacterMenuWidget::Close(UZZButtonBaseWidget* InButton)
{
	OnCloseMenu.Broadcast(this);
}