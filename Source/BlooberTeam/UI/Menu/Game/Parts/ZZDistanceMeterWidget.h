// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/RichTextBlock/ZZRichTextBlock.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "ZZDistanceMeterWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZDistanceMeterWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZRichTextBlock* TextRecordValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZRichTextBlock* TextCurrentDistance;

	UFUNCTION()
	void OnHamsterDistanceUpdate(int32 InDistance);

	UFUNCTION()
	void OnRecordChanged(int32 InDistance);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Transient)
	AZZHamsterActor* Hamster = nullptr;
};
