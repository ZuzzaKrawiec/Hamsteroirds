// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/ZZMenuBaseWidget.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "ZZGameMenuWidget.generated.h"

UCLASS()
class BLOOBERTEAM_API UZZGameMenuWidget : public UZZMenuBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonRestart;

	UFUNCTION()
	void OnHamsterSpawned(AZZHamsterActor* InHamster);

	UFUNCTION()
	void OnButtonRestartPressed(UZZButtonBaseWidget* InButton);

	UFUNCTION()
	void OnHamsterLaunched();

protected:
	virtual void NativeConstruct() override;
};
