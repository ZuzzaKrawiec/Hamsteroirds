// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Hamster/ZZHamsterActor.h"
#include "GameMode/ZZPawn.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Ability/ZZAbilityHamsterComponent.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"


AZZHamsterActor::AZZHamsterActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Spehre Collision"));
	SphereComponent->bEditableWhenInherited = true;

	HamsterMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(FName("Hamster Mesh"));
	HamsterMeshComponent->bEditableWhenInherited = true;

	RootComponent = SphereComponent;
	HamsterMeshComponent->SetupAttachment(SphereComponent);
}

void AZZHamsterActor::BeginPlay()
{
	Super::BeginPlay();
	
}
void AZZHamsterActor::StartFlying(FVector InVelocity)
{
	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	InVelocity *= 1.25f;

	if (UZZPowerupManagerComponent::GetPowerupStatic(GetWorld(), EPowerupIndex::ImpulseJump))
	{
		InVelocity *= 1.25f;
	}
	if (UZZPowerupManagerComponent::GetPowerupStatic(GetWorld(), EPowerupIndex::LessFriction))
	{
		SphereComponent->SetAngularDamping(4.0f);
	}


	Pawn->OnMainInteractionUsed.AddDynamic(this, &AZZHamsterActor::UsePower);
	FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, false);
	DetachFromActor(DetachmentTransformRules);
	SetActorEnableCollision(true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComponent->SetSimulatePhysics(true);	
	SphereComponent->SetPhysicsLinearVelocity(InVelocity, false);
	SetHamsterState(EHamsterState::Flying);
	GetWorld()->GetTimerManager().SetTimer(TimerCheckForStop, this, &AZZHamsterActor::CheckForStop, 0.1f, true, 0.0f);
	OnHamsterLaunched.Broadcast();
}

void AZZHamsterActor::PlacedOnLaunch()
{
	SetHamsterState(EHamsterState::PlacedOnLauncher);
	OnHamsterPlacedOnLaunch.Broadcast();
}
void AZZHamsterActor::UsePower()
{
	if (GetHamsterState() == EHamsterState::Stopped)
	{
		DieHamster();
		return;
	}
	
}
void AZZHamsterActor::DieHamster()
{
	OnHamsterDied.Broadcast();
}
void AZZHamsterActor::CheckForStop()
{
	if (GetHamsterState() != EHamsterState::Flying)
	{
		return;
	}
	if (GetVelocity().Length()>5.0f)
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(TimerCheckForStop);
	SetHamsterState(EHamsterState::Stopped);
	OnHamsterStopped.Broadcast();
}

float AZZHamsterActor::GetSpeed()
{
	return (SphereComponent->GetComponentVelocity()).Length();
}

void AZZHamsterActor::StartAbility()
{
	if (GetHamsterState() == EHamsterState::PlacedOnLauncher)
	{
		return;
	}
	TArray<UActorComponent*> OutComponents;
	GetComponents(OutComponents, false);
	for (UActorComponent* Component : OutComponents)
	{
		UZZAbilityHamsterComponent* Ability = Cast<UZZAbilityHamsterComponent>(Component);
		if (!Ability)
		{
			continue;
		}
		Ability->StartPower();
	}
}
void AZZHamsterActor::StopAbility()
{
	TArray<UActorComponent*> OutComponents;
	GetComponents(OutComponents, false);
	for (UActorComponent* Component : OutComponents)
	{
		UZZAbilityHamsterComponent* Ability = Cast<UZZAbilityHamsterComponent>(Component);
		if (!Ability)
		{
			continue;
		}
		Ability->StopPower();
	}
}