// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Game/Parts/ZZAvatarWidget.h"
#include "GameMode/ZZPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "Actors/Hamster/ZZHamsterData.h"

void UZZAvatarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!PlayerState)
	{
		return;
	}
	if (PlayerState->GetHamsterData())
	{
		OnHamsterDataChanged(PlayerState->GetHamsterData());
	}
	PlayerState->OnHamsterDataChanged.AddDynamic(this, &UZZAvatarWidget::OnHamsterDataChanged);

}
void UZZAvatarWidget::OnHamsterDataChanged(UZZHamsterData* InHamsterData)
{
	if (!InHamsterData)
	{
		return;
	}

	if (TextHamsterName)
	{
		TextHamsterName->SetText(InHamsterData->TextHamsterName);
		TextHamsterName->SetTextStyleSet(InHamsterData->HamsterNameStyle);
	}
	if (ImageHamster)
	{
		ImageHamster->SetBrushFromTexture(InHamsterData->Image);
	}
}