// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/ZZMenuBaseWidget.h"
#include "Components/WrapBox.h"
#include "ZZMenuShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZMenuShopWidget : public UZZMenuBaseWidget
{
	GENERATED_BODY()

public: 
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWrapBox* WrapBoxPowerups;

	UFUNCTION()
	void TryBuyPowerup(UZZShopPowerupWidget* InShopPowerupWidget);

	void CreatePowerups();


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonClose;

	UFUNCTION()
	void Close(UZZButtonBaseWidget* InButton);
private:
	virtual void NativeConstruct() override;
};
