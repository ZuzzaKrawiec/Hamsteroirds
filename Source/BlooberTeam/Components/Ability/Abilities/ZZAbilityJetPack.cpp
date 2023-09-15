// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Ability/Abilities/ZZAbilityJetPack.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Actors/Hamster/ZZHamsterActor.h"



void UZZAbilityJetPack::TriggerPowerDuration(float DeltaTime)
{
	Super::TriggerPowerDuration(DeltaTime);
	Hamster->GetSphereComponent()->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, 25.0f), true);
}