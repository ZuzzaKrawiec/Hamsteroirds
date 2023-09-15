// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZZMenuBaseWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOpenMenu, UZZMenuBaseWidget* InMenu, TSoftClassPtr<UZZMenuBaseWidget> InMenuWidgetClass);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCloseMenu, UZZMenuBaseWidget* InMenu);
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZMenuBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ClearDelegates();

	FOnOpenMenu OnOpenMenu;
	FOnCloseMenu OnCloseMenu;
};
