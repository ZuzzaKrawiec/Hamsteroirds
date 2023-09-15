// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Actors/Hamster/ZZHamsterData.h"
#include "Components/Image.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "UI/RichTextBlock/ZZRichTextBlock.h"
#include "ZZCharacterDetailsWidget.generated.h"


DECLARE_DELEGATE_OneParam(FOnCharacterSelected, UZZCharacterDetailsWidget* InCharacterDetailsWidget);

UCLASS()
class BLOOBERTEAM_API UZZCharacterDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetData(UZZHamsterData* InHamsterData);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	UImage* ImageHamsterMainIcon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	UZZRichTextBlock* TextHamsterName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	UZZRichTextBlock* TextHamsterClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	UZZRichTextBlock* TextHamsterAbility;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	UZZRichTextBlock* TextHamsterDesc;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	UZZButtonBaseWidget* ButtonSelect;

	UFUNCTION()
	void CharacterSelected(UZZButtonBaseWidget* InButton);

	FOnCharacterSelected OnCharacterSelected;
	UZZHamsterData* GetHamsterData() const;
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	void ReflectData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UZZHamsterData* HamsterData;



};
