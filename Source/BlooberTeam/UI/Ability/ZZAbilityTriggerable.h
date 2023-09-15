// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Ability/ZZAbilityWidget.h"
#include "Components/ProgressBar.h"
#include "ZZAbilityTriggerable.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZAbilityTriggerable : public UZZAbilityWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* ProgressBar;

	virtual void OnReadyChangedPost(bool bIsReady) override;
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	bool bUpdate = false;
	float StarTime = 0.0f;
};
