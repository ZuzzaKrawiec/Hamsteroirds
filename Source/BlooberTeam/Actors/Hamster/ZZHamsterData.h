// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/RichTextBlock/ZZRichTextDefines.h"
#include "ZZHamsterData.generated.h"

class AZZHamsterActor;
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZHamsterData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AZZHamsterActor> HamsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TextHamsterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTextStylePicker HamsterNameStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TextHamsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TextHamasterAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTextStylePicker HamsterBoldInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TextHamasterDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D * Image;
};
