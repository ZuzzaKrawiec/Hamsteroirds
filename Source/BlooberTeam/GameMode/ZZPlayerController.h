// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZZPlayerController.generated.h"


class AZZPawn;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePawnSpawned, AZZPawn*, InPawn);
UCLASS()
class BLOOBERTEAM_API AZZPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void CreateGamePawn();

	FOnGamePawnSpawned OnGamePawnSpawned;


};
