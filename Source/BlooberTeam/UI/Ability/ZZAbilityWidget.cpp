// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ability/ZZAbilityWidget.h"
#include "Components/Ability/ZZAbilityHamsterComponent.h"


void UZZAbilityWidget::SetData(UZZAbilityHamsterComponent* InAbilityHamsterComponent)
{
	if (!InAbilityHamsterComponent)
	{
		return;
	}
	AbilityHamsterComponent = InAbilityHamsterComponent;

	AbilityHamsterComponent->OnReadyChanged.AddDynamic(this, &UZZAbilityWidget::OnReadyChanged);
	if (AbilityHamsterComponent->GetHasDurability())
	{
		AbilityHamsterComponent->OnDurabilityChanged.AddDynamic(this, &UZZAbilityWidget::OnDurabilityChanged);
	}
}
void UZZAbilityWidget::OnDurabilityChanged(float CurrentDurability, float MaxDurability)
{
	OnDurabilityChangedPost(CurrentDurability, MaxDurability);
}

void UZZAbilityWidget::OnReadyChanged(bool bInIsReady)
{
	OnReadyChangedPost(bInIsReady);
}
void UZZAbilityWidget::OnDurabilityChangedPost(float CurrentDurability, float MaxDurability)
{

}
void UZZAbilityWidget::OnReadyChangedPost(bool bInIsReady)
{

}