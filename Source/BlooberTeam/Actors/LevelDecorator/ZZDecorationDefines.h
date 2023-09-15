// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ZZDecorationDefines.generated.h"

UENUM()
enum class EStylePlacementDecoration : uint8
{
	Horizontal = 0,
	Vertical,
	Cricle,
	StairsUp,
	StairsDown
};


class PositionGenerator
{
public:
	PositionGenerator() {};
	virtual ~PositionGenerator() {};
	virtual void Generate(FVector& InMiddlePoint, TArray<FVector>& InLocations) = 0;
};


class HorizontaGenerator : public PositionGenerator
{
public:
	HorizontaGenerator() {};
	~HorizontaGenerator() {};
	virtual void Generate(FVector& InMiddlePoint, TArray<FVector>& InLocations) override
	{
		for (int32 i = 0; i < InLocations.Num(); i++)
		{
			InLocations[i] = InMiddlePoint + (FVector(0.0f, i * 100.0f, 0.0));
		}
	}
};

class VerticalGenerator : public PositionGenerator
{
public:
	VerticalGenerator() {};
	~VerticalGenerator() {};
	virtual void Generate(FVector& InMiddlePoint, TArray<FVector>& InLocations) override
	{
		for (int32 i = 0; i < InLocations.Num(); i++)
		{
			InLocations[i] = InMiddlePoint + (FVector(0.0f, 0.0f, i * 100.0f));
		}
	}
};

class CircleGenerator : public PositionGenerator
{
public:
	CircleGenerator() {};
	~CircleGenerator() {};
	virtual void Generate(FVector& InMiddlePoint, TArray<FVector>& InLocations) override
	{
		float Step = FMath::DegreesToRadians(360.0f / InLocations.Num());
		float Spread = InLocations.Num() * 30.0f;
		for (int32 i = 0; i < InLocations.Num(); i++)
		{
			InLocations[i] = InMiddlePoint + (FVector(0.0f, FMath::Sin(Step * i) * Spread, FMath::Cos(Step * i) * Spread));
		}
	}
};

class StairsUpGenerator : public PositionGenerator
{
public:
	StairsUpGenerator() {};
	~StairsUpGenerator() {};
	virtual void Generate(FVector& InMiddlePoint, TArray<FVector>& InLocations) override
	{
		for (int32 i = 0; i < InLocations.Num(); i++)
		{
			InLocations[i] = InMiddlePoint + (FVector(0.0f, 100.0f * i, 100.0f * i));
		}
	}
};
class StairsDownGenerator : public PositionGenerator
{
public:
	StairsDownGenerator() {};
	~StairsDownGenerator() {};
	virtual void Generate(FVector& InMiddlePoint, TArray<FVector>& InLocations) override
	{
		for (int32 i = 0; i < InLocations.Num(); i++)
		{
			InLocations[i] = InMiddlePoint + (FVector(0.0f, 100.0f * i, -100.0f * i));
		}
	}
};


class StyleGenerator
{
public:
	static void GeneratePositions(FVector& InMiddlePoint, TArray<FVector>& InLocations, EStylePlacementDecoration InStyle)
	{
		PositionGenerator* GeneratorObj = nullptr;
		switch (InStyle)
		{
			case EStylePlacementDecoration::Horizontal:
			{
				GeneratorObj = new HorizontaGenerator();
				break;
			}
			case EStylePlacementDecoration::Vertical:
			{
				GeneratorObj = new VerticalGenerator();
				break;
			}
			case EStylePlacementDecoration::Cricle:
			{
				GeneratorObj = new CircleGenerator();
				break;
			}
			case EStylePlacementDecoration::StairsUp:
			{
				GeneratorObj = new StairsUpGenerator();
				break;
			}
			case EStylePlacementDecoration::StairsDown:
			{
				GeneratorObj = new StairsDownGenerator();
				break;
			}
		}
		GeneratorObj->Generate(InMiddlePoint, InLocations);
		delete GeneratorObj;
	};
};