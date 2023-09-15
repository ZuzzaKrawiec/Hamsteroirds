// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/LevelStreamingDynamic.h"
#include "ZZLevelStreamerDefines.generated.h"

class ULevelStreamingDynamic;

UENUM(Blueprinttype)
enum class EPartLevelType : uint8
{
	Normal,
	Trampoline
};
USTRUCT(Blueprinttype)
struct FLevelStreamChances
{
	GENERATED_USTRUCT_BODY()

public:
	FLevelStreamChances() {};
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Chance = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BonusChance  = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPartLevelType PartLevelType = EPartLevelType::Normal;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> WorldToStream;
};

USTRUCT(Blueprinttype)
struct FLevelStreamedData
{
	GENERATED_USTRUCT_BODY()

public:
	FLevelStreamedData() {};
	FLevelStreamedData(ULevelStreamingDynamic* InLevelStreamingDynamic, FTransform InTransform, int32 InGridIndex, bool bInShouldBeUnloaded) : LevelStreamingDynamic(InLevelStreamingDynamic), Transform(InTransform), GridIndex(InGridIndex), bShouldBeUnloaded(bInShouldBeUnloaded) {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ULevelStreamingDynamic* LevelStreamingDynamic;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform Transform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 GridIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bShouldBeUnloaded = true;

	bool Unload()
	{
		if (!bShouldBeUnloaded)
		{
			return false;
		}
		LevelStreamingDynamic->SetShouldBeLoaded(false);
		return true;
	}

};