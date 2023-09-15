// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UI/RichTextBlock/ZZRichTextBlock.h"
#include "ZZAvatarWidget.generated.h"

class UZZHamsterData;
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZAvatarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UZZRichTextBlock* TextHamsterName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ImageHamster;

	UFUNCTION()
	void OnHamsterDataChanged(UZZHamsterData* InHamsterData);
	
protected:
	virtual void NativeConstruct() override;
};
