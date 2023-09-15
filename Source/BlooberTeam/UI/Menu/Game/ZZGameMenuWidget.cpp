// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Game/ZZGameMenuWidget.h"
#include "GameMode/ZZPawn.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "Kismet/GameplayStatics.h"

void UZZGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonRestart->SetIsEnabled(false);
	ButtonRestart->OnButtonPressed.AddDynamic(this, &UZZGameMenuWidget::OnButtonRestartPressed);

	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	if (Pawn->GetHamsterActor())
	{
		OnHamsterSpawned(Pawn->GetHamsterActor());
	}
	Pawn->OnHamasterSpawned.AddDynamic(this, &UZZGameMenuWidget::OnHamsterSpawned);
}
void UZZGameMenuWidget::OnHamsterSpawned(AZZHamsterActor* InHamster)
{
	ButtonRestart->SetIsEnabled(false);
	InHamster->OnHamsterLaunched.AddDynamic(this, &UZZGameMenuWidget::OnHamsterLaunched);
}
void UZZGameMenuWidget::OnHamsterLaunched()
{
	ButtonRestart->SetIsEnabled(true);
}
void UZZGameMenuWidget::OnButtonRestartPressed(UZZButtonBaseWidget* InButton)
{
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	Pawn->UseRestartInteraction();
}