// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LevelStreamer/ZZLevelStreamerManagerComponent.h"
#include "Components/LevelStreamer/ZZLevelStreamerDefines.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/ZZPawn.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "Settings/ZZSettings.h"
#include "Global/ZZUtils.h"

UZZLevelStreamerManagerComponent::UZZLevelStreamerManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


void UZZLevelStreamerManagerComponent::StartEndlessStreaming()
{
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	if (Pawn->GetHamsterActor())
	{
		OnHamsterSpawned(Pawn->GetHamsterActor());
	}
	Pawn->OnHamasterSpawned.AddDynamic(this, &UZZLevelStreamerManagerComponent::OnHamsterSpawned);

}

void UZZLevelStreamerManagerComponent::RemoveRedundantLevels()
{
	for (auto Iterator = LevelsStreamed.CreateIterator(); Iterator; ++Iterator)
	{
		if (FMath::Abs(Iterator.Value().GridIndex - CurrentLoadedIndex) <= ChunkSize)
		{
			continue;
		}
		if (Iterator.Value().Unload())
		{
			LevelsStreamed.Remove(Iterator.Key());
		}
	}
}
void UZZLevelStreamerManagerComponent::CalculateChances()
{
	TotalChances = 0;
	for (const FLevelStreamChances& Data : GetDefault<UZZSettings>()->WorldsStreamData)
	{
		TotalChances += Data.Chance;
		if (Data.PartLevelType == EPartLevelType::Trampoline)
		{
			if (UZZPowerupManagerComponent::GetPowerupStatic(GetWorld(), EPowerupIndex::Trampolines))
			{
				TotalChances += Data.BonusChance;
			}
		}
	}
}
bool UZZLevelStreamerManagerComponent::GetRandomLevel(TSoftObjectPtr<UWorld>& LevelToStream)
{
	int32 RandomChance = UKismetMathLibrary::RandomInteger(TotalChances);
	int32 CalcChance = 0;
	int32 CumulatedChance = 0;
	for (const FLevelStreamChances& Data : GetDefault<UZZSettings>()->WorldsStreamData)
	{
		CalcChance += Data.Chance;
		if (Data.PartLevelType == EPartLevelType::Trampoline)
		{
			if (UZZPowerupManagerComponent::GetPowerupStatic(GetWorld(), EPowerupIndex::Trampolines))
			{
				CalcChance += Data.BonusChance;
			}
		}
		if (RandomChance < CalcChance)
		{
			LevelToStream = Data.WorldToStream;
			return true;
		}
	}
	return false;
}
void UZZLevelStreamerManagerComponent::StreamNeededLevels()
{
	for (int32 i = -ChunkSize; i < ChunkSize; i++)
	{
		int32 GridIndex = CurrentLoadedIndex + i;
		if (LevelsStreamed.Find(GridIndex))
		{
			continue;
		}
		TSoftObjectPtr<UWorld> LevelToStream;
		if (GetRandomLevel(LevelToStream))
		{
			AddStreamLevel(LevelToStream, GridIndex);
		}
	}
}
void UZZLevelStreamerManagerComponent::CheckForStreaming()
{
	int32 NewIndex = GetCurrentIndexNeeded();
	if (CurrentLoadedIndex == NewIndex)
	{
		return;
	}
	CurrentLoadedIndex = NewIndex;

	RemoveRedundantLevels();
	StreamNeededLevels();
}
void UZZLevelStreamerManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckForStreaming();
}
int32 UZZLevelStreamerManagerComponent::GetCurrentIndexNeeded()
{
	if (!HamsterActor)
	{
		return 0;
	}
	int32 YLoc = HamsterActor->GetActorLocation().Y;
	int32 Distance = YLoc + ((LevelWidth * FMath::Sign(YLoc)) / 2.0f);
	return Distance / LevelWidth;

}
void UZZLevelStreamerManagerComponent::OnHamsterSpawned(AZZHamsterActor* InHamster)
{
	if (!InHamster)
	{
		return;
	}
	CalculateChances();
	SetComponentTickEnabled(false);
	HamsterActor = InHamster;
	CurrentLoadedIndex = 0;
	RemoveRedundantLevels();
	StreamNeededLevels();
	HamsterActor->OnHamsterLaunched.AddDynamic(this, &UZZLevelStreamerManagerComponent::OnHamsterLaunched);
}

void UZZLevelStreamerManagerComponent::OnHamsterLaunched()
{
	SetComponentTickEnabled(true);
}
ULevelStreamingDynamic* UZZLevelStreamerManagerComponent::AddStreamLevel(TSoftObjectPtr<UWorld> World, int32 InGridIndex, bool bInShouldBeUnloaded)
{
	if (World.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("UZZLevelStreamerManagerComponent::AddStreamLevel world is null"))
			return nullptr;
	}
	bool bOutSuccess = false;
	FTransform Transform = FTransform::Identity;
	Transform.SetLocation(FVector(0.0f, InGridIndex * LevelWidth, 0.0f));

	ULevelStreamingDynamic* LevelStreamingDynamic = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GetWorld(), World, Transform, bOutSuccess);
	if (!bOutSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("UZZLevelStreamerManagerComponent::AddStreamLevel failed to stream"))
			return nullptr;
	}
	LevelsStreamed.Add(InGridIndex, FLevelStreamedData(LevelStreamingDynamic, Transform, InGridIndex, bInShouldBeUnloaded));
	return LevelStreamingDynamic;
}

void UZZLevelStreamerManagerComponent::RemoveStreamLevel()
{

}
void UZZLevelStreamerManagerComponent::RemoveAllStreamLevel()
{
}