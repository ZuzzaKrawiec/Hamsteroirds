// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Parallax/ZZParallaxOverlay.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Global/ZZUtils.h"

void UZZParallaxOverlay::NativeConstruct()
{
	Super::NativeConstruct();
	FindParallaxObjects();
}
void UZZParallaxOverlay::NativePreConstruct()
{
	Super::NativePreConstruct();
	FindParallaxObjects();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}
void UZZParallaxOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);;

	ParallaxEffectTick(InDeltaTime);
}
void UZZParallaxOverlay::ParallaxEffectTick(float InDeltaTime)
{
	if (!PlayerController)
	{
		return;	
	}
	float MouseX;
	float MouseY;
	PlayerController->GetMousePosition(MouseX, MouseY);
	FIntPoint ViewportSize;
	PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);

	if (MouseX > ViewportSize.X || MouseY>ViewportSize.Y || MouseX<0.0f || MouseY < 0.0f)
	{
		return;
	}
	for (UZZParallaxObjectWidget* ParallaxObject : ParallaxWidgetsFound)
	{
		ParallaxObject->ParallaxEffect(FVector2D(MouseX - (ViewportSize.X / 2), MouseY - (ViewportSize.Y / 2)));
	}
}
void UZZParallaxOverlay::FindParallaxObjects()
{
	TArray<UWidget*> OutWidgets;
	OutWidgets = CanvasContainer->GetAllChildren();
	for (UWidget* Widget : OutWidgets)
	{
		UZZParallaxObjectWidget* ParallaxObjectWidget = Cast<UZZParallaxObjectWidget>(Widget);
		if (ParallaxObjectWidget)
		{
			ParallaxWidgetsFound.Add(ParallaxObjectWidget);
		}
	}
}