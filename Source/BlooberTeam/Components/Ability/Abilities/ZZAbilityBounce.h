// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Ability/ZZAbilityHamsterComponent.h"
#include "ZZAbilityBounce.generated.h"

UCLASS(Blueprintable, Blueprinttype, meta = (BlueprintSpawnableComponent))
class BLOOBERTEAM_API UZZAbilityBounce : public UZZAbilityHamsterComponent
{
	GENERATED_BODY()
public:
	virtual void TriggerPower() override;
	virtual float GetCoolDownTime();
};

inline float UZZAbilityBounce::GetCoolDownTime()
{
	float Time = Super::GetCoolDownTime();
	if (bHasBonus)
	{
		Time *= 0.5f;
	}
	return Time;
}
