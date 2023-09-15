// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ability/ZZAbilityTriggerable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Ability/ZZAbilityHamsterComponent.h"

void UZZAbilityTriggerable::OnReadyChangedPost(bool bIsReady)
{
	if (!bIsReady)
	{
		StarTime = UGameplayStatics::GetTimeSeconds(GetWorld());
		bUpdate = true;
		ProgressBar->SetIsEnabled(false);
	}
	else
	{
		bUpdate = false;
		ProgressBar->SetPercent(1.0f);
		ProgressBar->SetIsEnabled(true);
	}
}
void UZZAbilityTriggerable::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,  InDeltaTime);
	if (bUpdate && AbilityHamsterComponent)
	{
		float Current = UGameplayStatics::GetTimeSeconds(GetWorld()) - StarTime;
		ProgressBar->SetPercent(Current / AbilityHamsterComponent->GetCoolDownTime());
	}
}