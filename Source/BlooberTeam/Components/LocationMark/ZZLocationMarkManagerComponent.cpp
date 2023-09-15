// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LocationMark/ZZLocationMarkManagerComponent.h"
#include "Actors/LocationMark/ZZLocationMarkActor.h"
#include "Global/ZZUtils.h"

UZZLocationMarkManagerComponent::UZZLocationMarkManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


bool UZZLocationMarkManagerComponent::MoveToMarker(UWorld* World, AActor* Actor, const FName& MarkerName)
{
	AZZGameState* GameState = UZZUtils::GetGameState(World);
	if (!GameState || !GameState->GetLocationMarkManagerComponent())
	{
		return false;
	}
	FTransform NewLocation = GameState->GetLocationMarkManagerComponent()->GetMarkTransform(MarkerName);
	Actor->SetActorTransform(NewLocation);
	return true;
}


void UZZLocationMarkManagerComponent::RegisterLocationMark(AZZLocationMarkActor* LocationMark)
{
	FLocationMarkData* LocationMarkData = Markers.Find(LocationMark->GetMarkName());
	if (!LocationMarkData)
	{

		Markers.Add(LocationMark->GetMarkName(), FLocationMarkData(LocationMark->GetActorTransform()));
		return;
	}
	LocationMarkData->AddTransform(LocationMark->GetActorTransform());
}
FTransform UZZLocationMarkManagerComponent::GetMarkTransform(const FName& Name) 
{
	FLocationMarkData* LocationMarkData = Markers.Find(Name);
	if (!LocationMarkData)
	{
		return FTransform::Identity;
	}
	return LocationMarkData->GetTransform();
}