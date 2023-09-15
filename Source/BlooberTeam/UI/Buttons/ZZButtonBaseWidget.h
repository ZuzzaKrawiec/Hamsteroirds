// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "UI/RichTextBlock/ZZRichTextBlock.h"
#include "Engine/DataTable.h"

#include "ZZButtonBaseWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressed, UZZButtonBaseWidget*, InButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonHovered, UZZButtonBaseWidget*, InButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonUnhovered, UZZButtonBaseWidget*, InButton);

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZButtonBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle ButtonStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTextStylePicker TextStyle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UZZRichTextBlock* ButtonText;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnButtonPressed OnButtonPressed;
	UFUNCTION()
	void OnButtonPresssedDelegate();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnButtonHovered OnButtonHovered;
	UFUNCTION()
	void OnButtonHoveredDelegate();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnButtonUnhovered OnButtonUnhovered;
	UFUNCTION()
	void OnButtonUnhoveredDelegate();

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void ReflectData();
	void ReflectButtonStyle();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText TextOnButton;
};
