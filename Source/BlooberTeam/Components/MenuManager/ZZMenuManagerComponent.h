// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/MenuManager/ZZMenuManagerDefines.h"
#include "ZZMenuManagerComponent.generated.h"

class UZZMenuBaseWidget;
class AZZPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class BLOOBERTEAM_API UZZMenuManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZZMenuManagerComponent();
		
	void OpenMenu(TSoftClassPtr<UZZMenuBaseWidget> InMenuWidgetClass, bool bOverlay = false);
	void OpenMenuDelegate(UZZMenuBaseWidget* InMenu, TSoftClassPtr<UZZMenuBaseWidget> InMenuWidgetClass);
	void CloseMenu(UZZMenuBaseWidget* InMenu);

	UFUNCTION()
	void OnGamePawnSpawned(AZZPawn* InPawn);
	UFUNCTION()
	void OpenMenuInteration(EMenuType InMenuType);
	void OpenMenuByEnum(EMenuType InMenuType, bool bOverlay = false);

	UZZMenuBaseWidget* GetCurrentOpenedMenuWidget() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UZZMenuBaseWidget* CurrentOpenedMenuWidget = nullptr;

	UPROPERTY()
	EMenuType CurrentMenuType = EMenuType::None;
};

inline UZZMenuBaseWidget* UZZMenuManagerComponent::GetCurrentOpenedMenuWidget() const
{
	return CurrentOpenedMenuWidget;
}