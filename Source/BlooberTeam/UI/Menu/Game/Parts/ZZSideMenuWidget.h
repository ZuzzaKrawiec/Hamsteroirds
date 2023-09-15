// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "ZZSideMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZSideMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonShop;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonChangeHamster;

	UFUNCTION()
	void OnShopPressed(UZZButtonBaseWidget* InButton);

	UFUNCTION()
	void OnChangeHamsterPressed(UZZButtonBaseWidget* InButton);

protected:
	virtual void NativeConstruct() override;
};
