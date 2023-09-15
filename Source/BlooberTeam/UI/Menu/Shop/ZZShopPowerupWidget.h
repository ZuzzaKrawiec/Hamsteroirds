// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Powerup/ZZPowerupData.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "UI/RichTextBlock/ZZRichTextBlock.h"
#include "Components/Image.h"
#include "ZZShopPowerupWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowerupBought, UZZShopPowerupWidget*, InShopPowerupWidget);
UCLASS()
class BLOOBERTEAM_API UZZShopPowerupWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetData(UZZPowerupData* InPowerupData);
	void Reflect();


	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UZZRichTextBlock* TextTitle;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UZZRichTextBlock* TextDescShort;

	UPROPERTY( BlueprintReadWrite, meta = (BindWidget))
	UZZRichTextBlock* TextDesc;

	UPROPERTY( BlueprintReadWrite, meta = (BindWidget))
	UImage* ImageHamster;

	UPROPERTY( BlueprintReadWrite, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonBuy;
	void Disable();
	UFUNCTION()
	void BuyPowerup(UZZButtonBaseWidget* InButton);
	FOnPowerupBought OnPowerupBought;

	UZZPowerupData* GetPowerupData() const;
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UZZPowerupData* PowerupData;
};

inline UZZPowerupData* UZZShopPowerupWidget::GetPowerupData() const
{
	return PowerupData;
}