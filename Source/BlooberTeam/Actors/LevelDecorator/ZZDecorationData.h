// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ZZDecorationData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BLOOBERTEAM_API UZZDecorationData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 MaxGridIndex;
};