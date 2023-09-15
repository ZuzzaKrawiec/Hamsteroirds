// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Camera/ZZCameraManagerComponent.h"
#include "GameMode/ZZPawn.h"
#include "GameMode/ZZGameState.h"
#include "Components/LocationMark/ZZLocationMarkManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Hamster/ZZHamsterActor.h"

UZZCameraManagerComponent::UZZCameraManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


void UZZCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
	{
		return;
	}
	CachedPawn = Cast<AZZPawn>(GetOwner());
	if (!CachedPawn)
	{
		return;
	}
	CachedPawn->OnHamasterSpawned.AddDynamic(this, &UZZCameraManagerComponent::OnHamsterSpawned);
}


void UZZCameraManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CameraFollowHamster(DeltaTime);
}

void UZZCameraManagerComponent::CameraFollowHamster(float DeltaTime)
{
	if (GetCameraState() != ECameraState::FollowingHamster)
	{
		return;
	}
	if (!CurrentHamster)
	{
		return;
	}
	FVector Velocity = CurrentHamster->GetVelocity();
	FVector HamsterLocation = CurrentHamster->GetActorLocation();
	

	float Speed = CurrentHamster->GetSpeed();
	float LagPower = 0.6f + UKismetMathLibrary::NormalizeToRange(CurrentHamster->GetSpeed(), 0.0f, 16000.0f);
	

 	LagLocation = UKismetMathLibrary::VInterpTo_Constant(LagLocation, CurrentHamster->GetActorLocation(), DeltaTime, FMath::Max(CurrentHamster->GetSpeed(), 250.0f) / LagPower);

	if (LagLocation.Y < CachedPawn->GetActorLocation().Y && Velocity.Y > 0.0f)
	{
		FVector Location = CachedPawn->GetActorLocation();
		Location.Z = CalculateCameraLocation().Z;
		CachedPawn->SetActorLocation(Location);
		return;
	}
	CachedPawn->SetActorLocation(CalculateCameraLocation());
}

FVector UZZCameraManagerComponent::CalculateCameraLocation()
{
	FVector CalcLoc = LagLocation + OffsetCamera;
	CalcLoc.Z = FMath::Clamp(CalcLoc.Z, MinClampValue, TNumericLimits< float >::Max());
	return CalcLoc;
}
void UZZCameraManagerComponent::OnHamsterSpawned(AZZHamsterActor* InHamsterActor)
{
	CurrentHamster = InHamsterActor;
	SetComponentTickEnabled(false);
	CurrentHamster->OnHamsterLaunched.AddDynamic(this, &UZZCameraManagerComponent::OnHamsterLaunched);
	CurrentHamster->OnHamsterPlacedOnLaunch.AddDynamic(this, &UZZCameraManagerComponent::OnHamsterPlacedOnLaunch);
	SetCameraState(ECameraState::WaitForBeingPlacedOnLaunch);
}
void UZZCameraManagerComponent::OnHamsterLaunched()
{	
	SetCameraState(ECameraState::FollowingHamster);
	SetComponentTickEnabled(true);
}
void UZZCameraManagerComponent::OnHamsterPlacedOnLaunch()
{
	
	LagLocation = CurrentHamster->GetActorLocation();
	UZZLocationMarkManagerComponent::MoveToMarker(GetWorld(), CachedPawn, MARKSTART);
	SetCameraState(ECameraState::WaitForLaunch);
}