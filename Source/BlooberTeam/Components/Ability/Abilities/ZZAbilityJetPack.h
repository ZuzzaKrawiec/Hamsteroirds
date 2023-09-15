// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Ability/ZZAbilityHamsterComponent.h"
#include "ZZAbilityJetPack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Blueprinttype, meta = (BlueprintSpawnableComponent))
class BLOOBERTEAM_API UZZAbilityJetPack : public UZZAbilityHamsterComponent
{
	GENERATED_BODY()

public:
	virtual void TriggerPowerDuration(float DeltaTime) override;

	virtual float GetRefillPower() override;
	virtual float GetDelayRefill() override;
};

inline float UZZAbilityJetPack::GetRefillPower()
{
	float Power = Super::GetRefillPower();
	if (bHasBonus)
	{
		Power *= 2.0f;
	}
	return Power;
}
inline float UZZAbilityJetPack::GetDelayRefill()
{
	float Power = Super::GetDelayRefill();
	if (bHasBonus)
	{
		Power *= 0.5f;
	}
	return Power;
}