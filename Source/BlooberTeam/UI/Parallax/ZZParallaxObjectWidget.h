// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "PaperSprite.h"

#include "ZZParallaxObjectWidget.generated.h"
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZParallaxObjectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BindWidget))
	UImage* ParallaxImage;

	void ParallaxEffect(FVector2D InVector);
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	void UpdateData();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UPaperSprite* PaperSprite = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RotationRate = 0.1f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ParallaxPowerMultiplier = 1.0f;
};
