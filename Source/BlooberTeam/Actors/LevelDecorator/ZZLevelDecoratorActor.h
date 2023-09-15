// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/LevelDecorator/ZZDecorationData.h"
#include "ZZLevelDecoratorActor.generated.h"



class AZZLevelDecorationActor;
UCLASS()
class BLOOBERTEAM_API AZZLevelDecoratorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AZZLevelDecoratorActor();

	void SpawnDecorations();
	void SpawnCoins();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(EditAnywhere)
	int32 DecorationAmount = 10;

	UPROPERTY(EditAnywhere)
	UZZDecorationData* DecorationData;

	UPROPERTY(EditAnywhere)
	float Spread = 500.0f;

	UPROPERTY()
	TArray<AZZLevelDecorationActor*> Decorations;
	
	UPROPERTY()
	TArray<AZZCoinActor*> CoinsSpawned;
};
