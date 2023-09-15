// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Hamster/ZZHamsterData.h"
#include "ZZHamsterActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHamsterLaunched);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHamsterPlacedOnLaunch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHamsterStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHamsterDied);


UENUM()
enum class EHamsterState : uint8
{
	None,
	PlacedOnLauncher,
	Flying,
	Stopped
};

class USphereComponent;
UCLASS()
class BLOOBERTEAM_API AZZHamsterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AZZHamsterActor();
	UStaticMeshComponent* GetHamsterMeshComponent() const;
	USphereComponent* GetSphereComponent() const;
	void StartFlying(FVector InVelocity);
	void PlacedOnLaunch();


	FOnHamsterLaunched OnHamsterLaunched;
	FOnHamsterPlacedOnLaunch OnHamsterPlacedOnLaunch;
	FOnHamsterStopped OnHamsterStopped;
	FOnHamsterDied OnHamsterDied;

	UFUNCTION()
	void UsePower();
	void DieHamster();
	void CheckForStop();

	float GetSpeed();

	EHamsterState GetHamsterState() const;
	void SetHamsterState(EHamsterState InHamsterState);

	EHamsterState HamsterState = EHamsterState::None;

	void StartAbility();
	void StopAbility();



protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* HamsterMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UZZHamsterData* HamsterData = nullptr;

	FTimerHandle TimerCheckForStop;
};
inline UStaticMeshComponent* AZZHamsterActor::GetHamsterMeshComponent() const
{
	return HamsterMeshComponent;
}
inline USphereComponent* AZZHamsterActor::GetSphereComponent() const
{
	return SphereComponent;
}
inline EHamsterState AZZHamsterActor::GetHamsterState() const
{
	return HamsterState;
}
inline void AZZHamsterActor::SetHamsterState(EHamsterState InHamsterState)
{
	HamsterState = InHamsterState;
}