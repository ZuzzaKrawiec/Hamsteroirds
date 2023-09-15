// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LocationMark/ZZLocationMarkActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/LocationMark/ZZLocationMarkManagerComponent.h"
#include "GameMode/ZZGameState.h"

AZZLocationMarkActor::AZZLocationMarkActor()
{
	PrimaryActorTick.bCanEverTick = true;
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	ArrowComponent->bEditableWhenInherited = true;
	RootComponent = ArrowComponent;
}
void AZZLocationMarkActor::BeginPlay()
{
	Super::BeginPlay();
	RegisterLocationMark();
	Destroy();
}


void AZZLocationMarkActor::RegisterLocationMark()
{
	AZZGameState* GameState = Cast<AZZGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (!GameState)
	{
		return;
	}
	UZZLocationMarkManagerComponent* LocationMarkManagerComponent = GameState->GetLocationMarkManagerComponent();
	if (!LocationMarkManagerComponent)
	{
		return;
	}
	LocationMarkManagerComponent->RegisterLocationMark(this);
	
}