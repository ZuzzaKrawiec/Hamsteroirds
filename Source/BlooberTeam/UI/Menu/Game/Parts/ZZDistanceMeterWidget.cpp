// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Game/Parts/ZZDistanceMeterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/ZZPawn.h"
#include "GameMode/ZZPlayerState.h"


void UZZDistanceMeterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	Pawn->OnHamsterDistanceUpdate.AddDynamic(this, &UZZDistanceMeterWidget::OnHamsterDistanceUpdate);

	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!PlayerState)
	{
		return;
	}
	PlayerState->OnRecordChanged.AddDynamic(this, &UZZDistanceMeterWidget::OnRecordChanged);
}
void UZZDistanceMeterWidget::OnHamsterDistanceUpdate(int32 InDistance)
{
	TextCurrentDistance->SetText(FText::Format(FText::FromString("{0}m"), InDistance));
}

void UZZDistanceMeterWidget::OnRecordChanged(int32 InDistance)
{
	TextRecordValue->SetText(FText::Format(FText::FromString("{0}m"), InDistance));
}