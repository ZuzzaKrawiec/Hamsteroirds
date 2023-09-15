// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Ability/Abilities/ZZAbilityBounce.h"
#include "Components/SphereComponent.h"
#include "Actors/Hamster/ZZHamsterActor.h"

void UZZAbilityBounce::TriggerPower()
{
	Super::TriggerPower();
	FVector Velocity = Hamster->GetSphereComponent()->GetComponentVelocity();
	Velocity.Z = -FMath::Abs(Velocity.Z) - 750.0f - (bHasBonus? 500.0f : 0.0);
	Hamster->GetSphereComponent()->SetPhysicsLinearVelocity(Velocity, false);
}