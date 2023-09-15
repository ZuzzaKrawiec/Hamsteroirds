// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/HorizontalBox.h"

#include "ZZAbilityHolderWidget.generated.h"

class AZZHamsterActor;
class UZZAbilityWidget;
UCLASS()
class BLOOBERTEAM_API UZZAbilityHolderWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* AbilitiesBox;

	UFUNCTION()
	void OnHamsterSpawned(AZZHamsterActor* InHamsterActor);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY()
	TArray<UZZAbilityWidget*> AbilityArray;
};
