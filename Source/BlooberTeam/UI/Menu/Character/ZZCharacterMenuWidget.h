// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/ZZMenuBaseWidget.h"

#include "UI/Menu/Character/ZZCharacterDetailsWidget.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "ZZCharacterMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZCharacterMenuWidget : public UZZMenuBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UZZCharacterDetailsWidget* Hamster1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UZZCharacterDetailsWidget* Hamster2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UZZCharacterDetailsWidget* Hamster3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UZZButtonBaseWidget* ButtonClose;

	void OnCharacterSelected(UZZCharacterDetailsWidget* InCharacterDetailsWidget);

	UFUNCTION()
	void Close(UZZButtonBaseWidget* InButton);
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
};
