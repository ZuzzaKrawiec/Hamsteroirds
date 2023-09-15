// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ZZPlayerState.h"
#include "GameMode/ZZPlayerController.h"
#include "GameMode/ZZPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"

AZZPlayerState::AZZPlayerState()
{
	PowerupManagerComponent = CreateDefaultSubobject<UZZPowerupManagerComponent>(FName("PowerupManagerComponent"));
	PowerupManagerComponent->bEditableWhenInherited = true;
}
void AZZPlayerState::BeginPlay()
{
	Super::BeginPlay();
	AZZPlayerController* PlayerController = Cast<AZZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController)
	{
		return;
	}
	PlayerController->OnGamePawnSpawned.AddDynamic(this, &AZZPlayerState::OnGamePawnSpawned);
}
void AZZPlayerState::OnGamePawnSpawned(AZZPawn* Pawn)
{
	if (!Pawn)
	{
		return;
	}
	Pawn->OnHamsterDistanceUpdate.AddDynamic(this, &AZZPlayerState::OnHamsterDistanceUpdate);
}
void AZZPlayerState::OnHamsterDistanceUpdate(int32 InDistance)
{
	if (DistanceRecord < InDistance)
	{
		DistanceRecord = InDistance;
		OnRecordChanged.Broadcast(DistanceRecord);
	}
}
UZZHamsterData* AZZPlayerState::GetHamsterData() const
{
	return HamsterData;
}
void AZZPlayerState::SetHamsterData(UZZHamsterData* InHamsterData)
{
	HamsterData = InHamsterData;
	OnHamsterDataChanged.Broadcast(InHamsterData);
}
int32 AZZPlayerState::GetCash() const
{
	return Cash;
}
void AZZPlayerState::SetCash(int32 InCash)
{
	Cash = InCash;
	OnCashChanged.Broadcast(Cash);
}
void AZZPlayerState::AddCash(int32 Add)
{
	SetCash(GetCash() + Add);
}