// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Global/ZZUtils.h"
#include "ZZLocationMarkDefines.generated.h"

USTRUCT(BlueprintType)
struct FLocationMarkData
{
	GENERATED_BODY()

	FLocationMarkData() {};
	FLocationMarkData(FTransform InTransform) 
	{	
		TransformArray.Add(InTransform);
	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FTransform> TransformArray;



	void AddTransform(FTransform InTransform)
	{
		TransformArray.Add(InTransform);
	}
	const FTransform& GetTransform()
	{
		if (!TransformArray.Num())
		{
			return FTransform::Identity;
		}
		return UZZUtils::GetRandom(TransformArray);
	}
};
