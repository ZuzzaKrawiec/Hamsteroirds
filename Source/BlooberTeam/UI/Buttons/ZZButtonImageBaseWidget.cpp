// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Buttons/ZZButtonImageBaseWidget.h"


void UZZButtonImageBaseWidget::ReflectData()
{
	Super::ReflectData();

	if (!ImageButton || !TextureImageButton)
	{
		return;
	}
	ImageButton->SetBrushFromTexture(TextureImageButton);
}
