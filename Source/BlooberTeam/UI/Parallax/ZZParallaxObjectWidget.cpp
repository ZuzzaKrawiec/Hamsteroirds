// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Parallax/ZZParallaxObjectWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Global/ZZUtils.h"


void UZZParallaxObjectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateData();
}
void UZZParallaxObjectWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateData();
}
void UZZParallaxObjectWidget::UpdateData()
{
	if (!PaperSprite)
	{
		return;
	}
	FSlateBrush Brush;
	Brush.SetResourceObject(PaperSprite);
	ParallaxImage->SetBrush(Brush);
}
void UZZParallaxObjectWidget::ParallaxEffect(FVector2D InVector)
{
	InVector *= ParallaxPowerMultiplier;
	SetRenderTranslation(InVector);
}
void UZZParallaxObjectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);	

	if (RotationRate != 0.0f)
	{
		SetRenderTransformAngle(GetRenderTransformAngle() + RotationRate);
	}
}