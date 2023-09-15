// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/RichTextBlock/ZZRichTextBlock.h"
#include "ZZCoinsWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZCoinsWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UZZRichTextBlock* TextCoinsAmount;

	UFUNCTION()
	void OnCashChanged(int32 InCash);
protected:
	virtual void NativeConstruct() override;

};
