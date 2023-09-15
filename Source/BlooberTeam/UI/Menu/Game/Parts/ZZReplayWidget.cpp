// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Game/Parts/ZZReplayWidget.h"
#include "GameMode/ZZPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Hamster/ZZHamsterActor.h"	


void UZZReplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	if (Pawn->GetHamsterActor())
	{
		OnHamsterSpawned(Pawn->GetHamsterActor());
	}
	Pawn->OnHamasterSpawned.AddDynamic(this, &UZZReplayWidget::OnHamsterSpawned);
}

void UZZReplayWidget::OnHamsterSpawned(AZZHamsterActor* InHamsterActor)
{
	HideReplay();
	InHamsterActor->OnHamsterStopped.AddDynamic(this, &UZZReplayWidget::ShowReplay);
}
void UZZReplayWidget::ShowReplay()
{	
	StopAnimation(AnimHide);
	PlayAnimation(AnimShow);
	bShown = true;
}
void UZZReplayWidget::HideReplay()
{
	if (!bShown)
	{
		return;
	}
	StopAnimation(AnimShow);
	PlayAnimation(AnimHide);
	bShown = false;
}