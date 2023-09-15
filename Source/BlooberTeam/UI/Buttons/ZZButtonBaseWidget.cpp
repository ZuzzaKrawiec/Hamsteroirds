// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "UI/Buttons/ZZButtonDefines.h"


void UZZButtonBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ReflectData();
	ReflectButtonStyle();

	Button->OnPressed.AddDynamic(this, &UZZButtonBaseWidget::OnButtonPresssedDelegate);
	Button->OnHovered.AddDynamic(this, &UZZButtonBaseWidget::OnButtonHoveredDelegate);
	Button->OnUnhovered.AddDynamic(this, &UZZButtonBaseWidget::OnButtonUnhoveredDelegate);
}
void UZZButtonBaseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	ReflectData();
	ReflectButtonStyle();
}
void UZZButtonBaseWidget::ReflectData()
{
	if (!ButtonText)
	{
		return;
	}
	ButtonText->SetText(TextOnButton);
	ButtonText->SetTextStyleSet(TextStyle);
}
void UZZButtonBaseWidget::ReflectButtonStyle()
{
	if (!Button)
	{
		return;
	}
	const UDataTable* DataTableStyles = ButtonStyle.DataTable.Get();
	if (!DataTableStyles)
	{
		return;
	}

	FButtonsStylesData* Style = DataTableStyles->FindRow<FButtonsStylesData>(ButtonStyle.RowName, FString("UZZButtonBaseWidget::ReflectButtonStyle"));
	if (!Style)
	{
		return;
	}
	Button->SetStyle(Style->ButtonStyle);
}



void UZZButtonBaseWidget::OnButtonUnhoveredDelegate()
{
	OnButtonUnhovered.Broadcast(this);
}
void UZZButtonBaseWidget::OnButtonHoveredDelegate()
{
	OnButtonHovered.Broadcast(this);
}
void UZZButtonBaseWidget::OnButtonPresssedDelegate()
{
	OnButtonPressed.Broadcast(this);
}