// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"
#include "Components/Image.h"
#include "ZZButtonImageBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZButtonImageBaseWidget : public UZZButtonBaseWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ImageButton;

protected:
	virtual void ReflectData() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* TextureImageButton;
};
