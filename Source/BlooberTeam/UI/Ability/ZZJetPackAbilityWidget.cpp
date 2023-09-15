// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ability/ZZJetPackAbilityWidget.h"


void UZZJetPackAbilityWidget::OnDurabilityChangedPost(float CurrentDurability, float MaxDurability)
{
	ProgressBar->SetPercent(CurrentDurability / MaxDurability);
}