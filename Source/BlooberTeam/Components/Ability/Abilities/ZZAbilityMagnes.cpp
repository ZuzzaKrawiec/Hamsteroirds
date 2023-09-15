// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Ability/Abilities/ZZAbilityMagnes.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "Actors/Coin/ZZCoinActor.h"


void UZZAbilityMagnes::TriggerPowerDuration(float DeltaTime)
{
	Super::TriggerPowerDuration(DeltaTime);
	FVector Loc = Hamster->GetActorLocation();
	FVector Dir = FVector::ZeroVector;
	for (UPrimitiveComponent* PrimitiveComponent : CoinsArray)
	{
		if (!PrimitiveComponent)
		{
			continue;
		}
		float Speed = 300.0+FMath::Max(0.0f, 500.0f-FVector::Dist(Dir, Loc));
		Dir = Loc - PrimitiveComponent->GetComponentLocation();
		Dir.Normalize(0.1f);
		PrimitiveComponent->SetPhysicsLinearVelocity(Dir * (Hamster->GetVelocity().Length() + Speed), false);
	}
}
void UZZAbilityMagnes::StartPower()
{
	Super::StartPower();

	float SphereSize = 400.0f + (bHasBonus ? 500.0f : 0.0f);

	MagnesSphere = Cast< USphereComponent>(Hamster->AddComponentByClass(USphereComponent::StaticClass(), false, FTransform::Identity, false));
	MagnesSphere->SetCollisionObjectType(ECC_WorldDynamic);
	MagnesSphere->SetSphereRadius(SphereSize);
	MagnesSphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	if (MagnesSphere)
	{
		TSet<AActor*> ActorsOverlap;
		MagnesSphere->GetOverlappingActors(ActorsOverlap, AZZCoinActor::StaticClass());
		for (AActor* Actor : ActorsOverlap)
		{
			AZZCoinActor* Coin = Cast<AZZCoinActor>(Actor);
			if (Coin)
			{
				AddCoin(Coin->GetSphereComponent());
			}
		}
		MagnesSphere->OnComponentBeginOverlap.AddDynamic(this, &UZZAbilityMagnes::AddCoinToArray);
	}
}
void UZZAbilityMagnes::StopPower()
{
	Super::StopPower();
	if (MagnesSphere)
	{
		MagnesSphere->DestroyComponent();
		CoinsArray.Empty();
	}
}
void UZZAbilityMagnes::AddCoinToArray(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<AZZCoinActor>(OtherActor))
	{
		return;
	}
	AddCoin(OtherComp);
}
void UZZAbilityMagnes::AddCoin(UPrimitiveComponent* CoinRoot)
{
	CoinRoot->SetEnableGravity(false);
	CoinRoot->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	CoinRoot->SetSimulatePhysics(true);
	CoinsArray.Add(CoinRoot);
}