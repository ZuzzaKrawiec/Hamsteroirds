// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Components/LevelStreamer/ZZLevelStreamerDefines.h"
#include "GameMode/ZZPawn.h"
#include "ZZSettings.generated.h"


class AZZLevelDecorationActor;
class AZZCoinActor;
UCLASS(config = Game, defaultconfig, BlueprintType)
class BLOOBERTEAM_API UZZSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, Category = "Level Streamer")
	TArray<FLevelStreamChances> WorldsStreamData;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly, Category = "Level Streamer")
	TSoftObjectPtr<UWorld> WorldStart;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AZZPawn> GamePawn;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AZZLevelDecorationActor> DecorationActor;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AZZCoinActor> CoinClass;
};
