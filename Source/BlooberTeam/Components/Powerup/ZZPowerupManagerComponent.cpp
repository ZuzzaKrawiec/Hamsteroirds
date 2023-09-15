// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Powerup/ZZPowerupManagerComponent.h"
#include "Components/Powerup/ZZPowerupData.h"
#include "GameMode/ZZPlayerState.h"
#include "Kismet/GameplayStatics.h"

UZZPowerupManagerComponent::UZZPowerupManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UZZPowerupManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UZZPowerupManagerComponent::AddPowerup(EPowerupIndex InPowerupIndex)
{
	PowerupState.Add(InPowerupIndex, true);
}
bool UZZPowerupManagerComponent::GetPowerup(EPowerupIndex InPowerupIndex)
{
	if (!PowerupState.Contains(InPowerupIndex))
	{
		return false;
	}
	return *PowerupState.Find(InPowerupIndex);
}

const TArray<TSoftObjectPtr<UZZPowerupData>>& UZZPowerupManagerComponent::GetPowerupsData() const
{
	return PowerupsData;
}

bool UZZPowerupManagerComponent::GetPowerupStatic(UWorld* World, EPowerupIndex InPowerupIndex)
{
	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(World,0));
	if (!PlayerState)
	{
		return false;
	}
	if (!PlayerState->GetPowerupManagerComponent())
	{
		return false;
	}
	return PlayerState->GetPowerupManagerComponent()->GetPowerup(InPowerupIndex);
}