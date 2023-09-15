// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelDecorator/ZZLevelDecoratorActor.h"
#include "Actors/LevelDecorator/ZZLevelDecorationActor.h"
#include "Actors/LevelDecorator/ZZDecorationDefines.h"
#include "GameMode/ZZPawn.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/Coin/ZZCoinActor.h"
#include "Global/ZZUtils.h"
#include "Settings/ZZSettings.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"

AZZLevelDecoratorActor::AZZLevelDecoratorActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AZZLevelDecoratorActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnDecorations();

	SpawnCoins();
}
void AZZLevelDecoratorActor::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
void AZZLevelDecoratorActor::SpawnDecorations()
{
	if (GetDefault<UZZSettings>()->DecorationActor.IsNull())
	{
		return;
	}

	FVector Middle = GetActorLocation();
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn)
	{
		Middle.Z = Pawn->GetHamsterActor()->GetActorLocation().Z;
	}


	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.Owner = this;
	FTransform Transform = FTransform::Identity;;
	for (int32 i = 0; i < DecorationAmount; i++)
	{
		float Scale = UKismetMathLibrary::RandomFloatInRange(0.2f, 1.5f);
		float Distance = (1.0f - Scale) * 1550.0f;
		Transform.SetLocation(FVector(Middle.X + Distance, Middle.Y + UKismetMathLibrary::RandomIntegerInRange(-500.0f, 500.0), Middle.Z + UKismetMathLibrary::RandomFloat() * Spread));
		Transform.SetScale3D(FVector(Scale));
		AZZLevelDecorationActor* Decoration = GetWorld()->SpawnActor<AZZLevelDecorationActor>(GetDefault<UZZSettings>()->DecorationActor.LoadSynchronous(), Transform, Params);
		if (!Decoration)
		{
			continue;
		}
		Decoration->SetData(DecorationData);
		Decorations.Add(Decoration);
	}
}
void AZZLevelDecoratorActor::SpawnCoins()
{	
	if (GetDefault<UZZSettings>()->CoinClass.IsNull())
	{
		return;
	}
	bool bMoreCoins = UZZPowerupManagerComponent::GetPowerupStatic(GetWorld(), EPowerupIndex::MoreCoins);
	if (UKismetMathLibrary::RandomInteger(100) > 40 + (bMoreCoins ? 30 : 0))
	{
		return;
	}

	FVector Middle = GetActorLocation();
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Pawn)
	{
		Middle.Z = Pawn->GetHamsterActor()->GetActorLocation().Z;
		if (Pawn->GetHamsterActor()->GetVelocity().Z > 0.0f)
		{
			Middle.Z += UKismetMathLibrary::RandomFloatInRange(0.0f, 150.0);
		}
		else
		{
			Middle.Z -= UKismetMathLibrary::RandomFloatInRange(0.0f, 150.0f);
		}
		
	}
	Middle.Z = FMath::Clamp(Middle.Z, 140.0f, TNumericLimits<float>::Max());

	int32 AmountToSpawn = UKismetMathLibrary::RandomIntegerInRange(3,5);
	if (bMoreCoins)
	{
		AmountToSpawn += 5;
	}
	
	TArray<FVector> InLocations;
	InLocations.Init(FVector::ZeroVector, AmountToSpawn);

	TArray<EStylePlacementDecoration> Placements = 
	{
		EStylePlacementDecoration::Vertical,
		EStylePlacementDecoration::Horizontal,
		EStylePlacementDecoration::Cricle,
		EStylePlacementDecoration::StairsUp,
		EStylePlacementDecoration::StairsDown
	};
	

	StyleGenerator::GeneratePositions(Middle, InLocations, UZZUtils::GetRandom(Placements));
	FActorSpawnParameters Params;
	FTransform Transform = FTransform::Identity;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.Owner = this;
	for (FVector& CoinLocation : InLocations)
	{
		CoinLocation.Z = FMath::Clamp(CoinLocation.Z, 140.0f, TNumericLimits<float>::Max());
		Transform.SetLocation(CoinLocation);
		AZZCoinActor* Coin = GetWorld()->SpawnActor<AZZCoinActor>(GetDefault<UZZSettings>()->CoinClass.LoadSynchronous(), Transform, Params);
		if (!Coin)
		{
			continue;
		}
		CoinsSpawned.Add(Coin);
	}
}