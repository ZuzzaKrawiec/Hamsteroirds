// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/LevelStreamer/ZZLevelStreamerDefines.h"
#include "ZZLevelStreamerManagerComponent.generated.h"

class AZZHamsterActor;
class ULevelStreamingDynamic;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class BLOOBERTEAM_API UZZLevelStreamerManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZZLevelStreamerManagerComponent();

	void StartEndlessStreaming();

	void RemoveRedundantLevels();
	void CalculateChances(); 
	bool GetRandomLevel(TSoftObjectPtr<UWorld>& LevelToStream);
	void StreamNeededLevels();
	void CheckForStreaming();

	int32 GetCurrentIndexNeeded();

	UFUNCTION()
	void OnHamsterSpawned(AZZHamsterActor* InHamster);

	UFUNCTION()
	void OnHamsterLaunched();

	UFUNCTION(BlueprintCallable)
	ULevelStreamingDynamic* AddStreamLevel(TSoftObjectPtr<UWorld> World, int32 InGridIndex, bool bInShouldBeUnloaded = true);

	UFUNCTION(BlueprintCallable)
	void RemoveStreamLevel();

	UFUNCTION(BlueprintCallable)
	void RemoveAllStreamLevel();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	int32 TotalChances = 0;

	UPROPERTY()
	TMap<int32, FLevelStreamedData> LevelsStreamed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LevelWidth = 400.0f;

	UPROPERTY(BlueprintReadOnly)
	int32 EndlessIndex = 0;

	//We Stream Current and chunkSize next/prev
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 ChunkSize = 2;

	UPROPERTY()
	int32 CurrentLoadedIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	AZZHamsterActor* HamsterActor = nullptr;
};
