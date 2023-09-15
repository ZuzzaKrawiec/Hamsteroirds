// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Ability/ZZAbilityHamsterComponent.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"

UZZAbilityHamsterComponent::UZZAbilityHamsterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bHasBonus = UZZPowerupManagerComponent::GetPowerupStatic(GetWorld(), EPowerupIndex::BaseAbility);
}


void UZZAbilityHamsterComponent::BeginPlay()
{
	Super::BeginPlay();
	Hamster = Cast<AZZHamsterActor>(GetOwner());
}


void UZZAbilityHamsterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsUsing)
	{
		ConsumeDuration(DeltaTime);
	}
}
void UZZAbilityHamsterComponent::ConsumeDuration(float DeltaTime)
{
	SetCurrentDurability(FMath::Max(CurrentDurability - (ConsumeDurability * DeltaTime), 0.0f));
	TriggerPowerDuration(DeltaTime);
	if (CurrentDurability <= 0.0f)
	{
		StopPower();
	}
}

void UZZAbilityHamsterComponent::TriggerPowerDuration(float DeltaTime)
{

}


void UZZAbilityHamsterComponent::StartPower()
{
	if (!IsReady())
	{
		return;
	}
	bIsUsing = true;
	SetComponentTickEnabled(bHasDurability);
	TriggerPower();
}
void UZZAbilityHamsterComponent::StopPower()
{
	bIsUsing = false;
	SetComponentTickEnabled(false);
	if (bHasDurability)
	{
		GetWorld()->GetTimerManager().SetTimer(DelayRefillTimer, this, &UZZAbilityHamsterComponent::RefillTick, 0.1f, true, GetDelayRefill());
	}
}
void UZZAbilityHamsterComponent::RefillTick()
{
	SetCurrentDurability(FMath::Min(MaxDurability, CurrentDurability + GetRefillPower()));
}
bool UZZAbilityHamsterComponent::IsReady()
{
	if (bHasDurability)
	{
		return CurrentDurability > 0.0f;
	}
	return bIsReady;
}
void UZZAbilityHamsterComponent::TriggerPower()
{
	if (!bHasDurability)
	{
		SetIsReady(false);
		GetWorld()->GetTimerManager().SetTimer(CoolDownTimer, this, &UZZAbilityHamsterComponent::CoolDownReset, CoolDownTime, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(DelayRefillTimer);
	}
}

void UZZAbilityHamsterComponent::CoolDownReset()
{
	Refil();
}
void UZZAbilityHamsterComponent::Refil()
{
	SetIsReady(true);
}

void UZZAbilityHamsterComponent::SetCurrentDurability(float InDurability)
{
	CurrentDurability = InDurability;
	OnDurabilityChanged.Broadcast(CurrentDurability, MaxDurability);
}

void UZZAbilityHamsterComponent::SetIsReady(bool bInIsReady)
{
	bIsReady = bInIsReady;
	OnReadyChanged.Broadcast(bIsReady);
}