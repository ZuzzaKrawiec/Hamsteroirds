// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Character/ZZCharacterDetailsWidget.h"


void UZZCharacterDetailsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReflectData();

	ButtonSelect->OnButtonPressed.AddDynamic(this, &UZZCharacterDetailsWidget::CharacterSelected);
}
void UZZCharacterDetailsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	ReflectData();
}

void UZZCharacterDetailsWidget::SetData(UZZHamsterData* InHamsterData)
{
	HamsterData = InHamsterData;
	ReflectData();
}
void UZZCharacterDetailsWidget::CharacterSelected(UZZButtonBaseWidget* InButton)
{
	OnCharacterSelected.ExecuteIfBound(this);
	OnCharacterSelected.Unbind();
}
void UZZCharacterDetailsWidget::ReflectData()
{
	if (!HamsterData)
	{
		return;
	}
	if (TextHamsterName)
	{
		TextHamsterName->SetText(HamsterData->TextHamsterName);
		TextHamsterName->SetTextStyleSet(HamsterData->HamsterNameStyle);
	}
	if (TextHamsterClass)
	{
		TextHamsterClass->SetText(HamsterData->TextHamsterClass);
		TextHamsterClass->SetTextStyleSet(HamsterData->HamsterBoldInfo);
	}
	if (TextHamsterAbility)
	{
		TextHamsterAbility->SetText(HamsterData->TextHamasterAbility);
		TextHamsterAbility->SetTextStyleSet(HamsterData->HamsterBoldInfo);
	}
	if (TextHamsterDesc)
	{
		TextHamsterDesc->SetText(HamsterData->TextHamasterDesc);
	}
	if (ImageHamsterMainIcon)
	{
		ImageHamsterMainIcon->SetBrushFromTexture(HamsterData->Image);
	}
}

UZZHamsterData* UZZCharacterDetailsWidget::GetHamsterData() const
{
	return HamsterData;
}