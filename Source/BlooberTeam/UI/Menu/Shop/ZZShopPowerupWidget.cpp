// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Shop/ZZShopPowerupWidget.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"
#include "GameMode/ZZPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UZZShopPowerupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonBuy)
	{
		ButtonBuy->OnButtonPressed.AddDynamic(this, &UZZShopPowerupWidget::BuyPowerup);
	}
}
void UZZShopPowerupWidget::NativePreConstruct()
{
	Super::NativeConstruct();
	Reflect();
}
void UZZShopPowerupWidget::SetData(UZZPowerupData* InPowerupData)
{
	PowerupData = InPowerupData;
	Reflect();
}
void UZZShopPowerupWidget::Reflect()
{
	if (!PowerupData)
	{
		return;
	}
	if (TextTitle)
	{
		TextTitle->SetText(PowerupData->Title);
	}
	if (TextDescShort)
	{
		TextDescShort->SetText(PowerupData->DescShort);
	}
	if (TextDesc)
	{
		TextDesc->SetText(PowerupData->Desc);
	}
	if (ImageHamster)
	{
		ImageHamster->SetBrushFromTexture(PowerupData->Icon);
	}
	if (ButtonBuy)
	{
		ButtonBuy->ButtonText->SetText(FText::Format(FText::FromString("{0}$"), PowerupData->Cost));
	}
	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!PlayerState)
	{
		return;
	}
	UZZPowerupManagerComponent* PowerupManagerComponent = PlayerState->GetPowerupManagerComponent();
	if (!PowerupManagerComponent)
	{
		return;
	}
	ButtonBuy->SetIsEnabled(!PowerupManagerComponent->GetPowerup(PowerupData->PowerupIndex));

}

void UZZShopPowerupWidget::Disable()
{
	ButtonBuy->SetIsEnabled(false);
}
void UZZShopPowerupWidget::BuyPowerup(UZZButtonBaseWidget* InButton)
{
	OnPowerupBought.Broadcast(this);
}