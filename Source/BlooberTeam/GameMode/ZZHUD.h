// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ZZHUD.generated.h"

class UZZMenuManagerComponent;
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API AZZHUD : public AHUD
{
	GENERATED_BODY()
public:
	AZZHUD();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UZZMenuManagerComponent* GetMenuManagerComponent();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UZZMenuManagerComponent* MenuManagerComponent;
};

inline UZZMenuManagerComponent* AZZHUD::GetMenuManagerComponent()
{
	return MenuManagerComponent;
}
