// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "ZZReplayWidget.generated.h"

class AZZHamsterActor;
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZReplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnHamsterSpawned(AZZHamsterActor* InHamsterActor);

	UFUNCTION()
	void ShowReplay();
	void HideReplay();

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimShow;

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* AnimHide;

protected:
	virtual void NativeConstruct() override;

	bool bShown = false;
	
};
