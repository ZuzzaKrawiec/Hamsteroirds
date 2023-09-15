// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/ZZMenuBaseWidget.h"
#include "Components/Image.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "ZZMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZMainMenuWidget : public UZZMenuBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonStartGame;
	UFUNCTION()
	void StartGame(UZZButtonBaseWidget* InButton);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonSettings;
	UFUNCTION()
	void OpenSettings(UZZButtonBaseWidget* InButton);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonQuit;
	UFUNCTION()
	void QuitButton(UZZButtonBaseWidget* InButton);

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
};
