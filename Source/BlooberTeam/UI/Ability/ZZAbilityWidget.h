// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZZAbilityWidget.generated.h"

class UZZAbilityHamsterComponent;
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetData(UZZAbilityHamsterComponent* InAbilityHamsterComponent);

	UFUNCTION()
	void OnDurabilityChanged(float CurrentDurability, float MaxDurability);
	virtual void OnDurabilityChangedPost(float CurrentDurability, float MaxDurability);

	UFUNCTION()
	void OnReadyChanged(bool bInIsReady);
	virtual void OnReadyChangedPost(bool bInIsReady);

protected:
	UPROPERTY()
	UZZAbilityHamsterComponent* AbilityHamsterComponent = nullptr;
};
