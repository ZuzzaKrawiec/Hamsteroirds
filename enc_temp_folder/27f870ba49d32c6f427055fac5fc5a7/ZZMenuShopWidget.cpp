// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Shop/ZZMenuShopWidget.h"
#include "GameMode/ZZPlayerState.h"
#include "UI/Menu/Shop/ZZShopPowerupWidget.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"
#include "Components/Powerup/ZZPowerupData.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/ZZUISettings.h"


void UZZMenuShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CreatePowerups();
}
void UZZMenuShopWidget::CreatePowerups()
{
	if (GetDefault<UZZUISettings>()->ShopPowerupWidgetClass.IsNull() || !WrapBoxPowerups)
	{
		return;
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
	for (const TSoftObjectPtr<UZZPowerupData> PowerupSoftData : PowerupManagerComponent->GetPowerupsData())
	{
		if (PowerupSoftData.IsNull())
		{
			continue;
		}
		UZZPowerupData* PowerupData = PowerupSoftData.LoadSynchronous();
		if (!PowerupData)
		{
			continue;
		}

		UZZShopPowerupWidget* ShopPowerupWidget = Cast<UZZShopPowerupWidget>(CreateWidget(GetOwningPlayer(), GetDefault<UZZUISettings>()->ShopPowerupWidgetClass.LoadSynchronous()));
		if (!ShopPowerupWidget)
		{
			continue;
		}		
		WrapBoxPowerups->AddChildToWrapBox(ShopPowerupWidget);
		ShopPowerupWidget->SetData(PowerupData);
		ShopPowerupWidget->OnPowerupBought.AddDynamic(this, &UZZMenuShopWidget::TryBuyPowerup);
	}
}
void UZZMenuShopWidget::TryBuyPowerup(UZZShopPowerupWidget* InShopPowerupWidget)
{
	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!PlayerState)
	{
		return;
	}
	UZZPowerupData* PowerupData = InShopPowerupWidget->GetPowerupData();
	if (!PowerupData)
	{
		return;
	}

	if (PlayerState->GetCash() < PowerupData->Cost)
	{
		return;
	}

	UZZPowerupManagerComponent* PowerupManagerComponent = PlayerState->GetPowerupManagerComponent();
	if (!PowerupManagerComponent || PowerupManagerComponent->GetPowerup(PowerupData->PowerupIndex))
	{
		return;
	}
	InShopPowerupWidget->Disable();
	PlayerState->AddCash(-PowerupData->Cost);
	PowerupManagerComponent->AddPowerup(PowerupData->PowerupIndex);
}