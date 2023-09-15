// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"
#include "ZZPowerupData.generated.h"


UCLASS()
class BLOOBERTEAM_API UZZPowerupData : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPowerupIndex PowerupIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DescShort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;

};
