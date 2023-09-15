// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Components/MenuManager/ZZMenuManagerDefines.h"
#include "ZZUISettings.generated.h"

class UZZMenuBaseWidget;
class UZZShopPowerupWidget;
/**
 * 
 */
UCLASS(config = Game, defaultconfig, BlueprintType)
class BLOOBERTEAM_API UZZUISettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Class")
	TMap<EMenuType, TSoftClassPtr<UZZMenuBaseWidget>> MenuWidgetClass;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Class")
	TSoftClassPtr<UZZShopPowerupWidget> ShopPowerupWidgetClass;
};
