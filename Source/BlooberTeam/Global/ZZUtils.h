// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameMode/ZZGameState.h"

#include "ZZUtils.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API UZZUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	template <class T>
	static T GetRandom(const TArray<T>& Arr)
	{
		if (Arr.Num() <= 0)
		{
			return T();
		}
		return Arr[UKismetMathLibrary::RandomInteger(Arr.Num())];
	}

	static AZZGameState* GetGameState(UWorld* World);
};

