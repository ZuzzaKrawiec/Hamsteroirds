// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Overlay.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Parallax/ZZParallaxObjectWidget.h"
#include "PaperSprite.h"

#include "ZZParallaxOverlay.generated.h"
class UZZParallaxObjectData;
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZParallaxOverlay : public UUserWidget
{
	GENERATED_BODY()
public: 
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UOverlay* OverlayContainer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* CanvasContainer;

	UPROPERTY()
	TArray<UZZParallaxObjectWidget*> ParallaxWidgetsFound;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<UZZParallaxObjectWidget> ParallaxObjectWidgetClass;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	void ParallaxEffectTick(float InDeltaTime);
	void FindParallaxObjects();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 ElemetsAmount = 5;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	APlayerController* PlayerController = nullptr;
	
};
