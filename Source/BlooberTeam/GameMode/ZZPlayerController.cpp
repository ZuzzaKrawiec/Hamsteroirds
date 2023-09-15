// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ZZPlayerController.h"
#include "Settings/ZZSettings.h"
#include "GameMode/ZZPawn.h"
#include "GameMode/ZZGameState.h"
#include "Components/LocationMark/ZZLocationMarkManagerComponent.h"
#include "Kismet/GameplayStatics.h"


void AZZPlayerController::CreateGamePawn()
{
	if (GetDefault<UZZSettings>()->GamePawn.IsNull())
	{
		return;
	}
	FTransform Transform = FTransform::Identity;
	AZZGameState* GameState = Cast<AZZGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
		if (GameState->GetLocationMarkManagerComponent())
		{
			Transform = GameState->GetLocationMarkManagerComponent()->GetMarkTransform(MARKSTART);
		}
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TSubclassOf<AZZPawn> PawnClass = GetDefault<UZZSettings>()->GamePawn.LoadSynchronous();
	AZZPawn* PawnSpawned = GetWorld()->SpawnActor<AZZPawn>(PawnClass, Transform, Params);
	Possess(PawnSpawned);
	PawnSpawned->SpawnHamster();
	OnGamePawnSpawned.Broadcast(PawnSpawned);
}
