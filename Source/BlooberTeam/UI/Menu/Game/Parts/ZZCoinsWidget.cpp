// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Game/Parts/ZZCoinsWidget.h"
#include "GameMode/ZZPlayerState.h"
#include "Kismet/GameplayStatics.h"


void UZZCoinsWidget::NativeConstruct() 
{
	Super::NativeConstruct();


	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!PlayerState)
	{
		return;
	}
	OnCashChanged(PlayerState->GetCash());
	PlayerState->OnCashChanged.AddDynamic(this, &UZZCoinsWidget::OnCashChanged);
}
void UZZCoinsWidget::OnCashChanged(int32 InCash)
{
	if(!TextCoinsAmount)
	{
		return;
	}

	TextCoinsAmount->SetText(FText::AsNumber(InCash));
}