// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Ability/ZZAbilityWidget.h"
#include "Components/ProgressBar.h"
#include "ZZJetPackAbilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZJetPackAbilityWidget : public UZZAbilityWidget
{
	GENERATED_BODY()
public: 
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* ProgressBar;

	
	virtual void OnDurabilityChangedPost(float CurrentDurability, float MaxDurability) override;
};
