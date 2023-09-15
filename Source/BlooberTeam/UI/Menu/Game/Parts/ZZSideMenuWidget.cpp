// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Game/Parts/ZZSideMenuWidget.h"
#include "GameMode/ZZPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MenuManager/ZZMenuManagerComponent.h"


void UZZSideMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonShop->OnButtonPressed.AddDynamic(this, &UZZSideMenuWidget::OnShopPressed);
	ButtonChangeHamster->OnButtonPressed.AddDynamic(this, &UZZSideMenuWidget::OnChangeHamsterPressed);
}
void UZZSideMenuWidget::OnShopPressed(UZZButtonBaseWidget* InButton)
{
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	Pawn->OpenMenuInteracton(EMenuType::Shop);
}
void UZZSideMenuWidget::OnChangeHamsterPressed(UZZButtonBaseWidget* InButton)
{
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	Pawn->OpenMenuInteracton(EMenuType::ChangeHamster);
}