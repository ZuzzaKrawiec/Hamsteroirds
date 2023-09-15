// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlock.h"
#include "UI/RichTextBlock/ZZRichTextDefines.h"
//#include "ZZTextStylePicker.h"
#include "ZZRichTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZRichTextBlock : public URichTextBlock
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTextStylePicker StylePicker;

	virtual void SetTextStyleSet(const FTextStylePicker& InTextStyleBlock);
	
protected:
	virtual void UpdateStyleData() override;
	virtual void InternalRebuildStyleInstance();
};
