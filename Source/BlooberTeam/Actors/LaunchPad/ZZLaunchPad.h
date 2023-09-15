// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZZLaunchPadDefines.h"
#include "ZZLaunchPad.generated.h"

class AZZPawn;
class AZZHamsterActor;
class UPhysicsConstraintComponent;
class USkeletalMechComponent;
class UStaticMeshComponent;
class UCableComponent;

UCLASS()
class BLOOBERTEAM_API AZZLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	AZZLaunchPad();
	virtual void Tick(float DeltaTime) override;

	void SaveStartingState();
	UFUNCTION(BlueprintCallable)
	void LaunchPadSimulation(bool bState);
	void ReleaseHamster();
	UFUNCTION(BlueprintCallable)
	void RestoreStartingState();

	UFUNCTION()
	void PlaceHamster(AZZHamsterActor* InHamsterActor);
	UFUNCTION()
	void TriggerLaunchPadBehavior();
	UFUNCTION()
	void BindBehavior(AZZPawn* InPawn);
	void WaitForPawn();


	void SetLaunchPadState(ELaunchPadState InLaunchPadState);
	ELaunchPadState GetLaunchPadState() const;
protected:
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	USkeletalMeshComponent* JetLaunchPad = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UStaticMeshComponent* ArmLaunchPad = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UStaticMeshComponent* WeightLaunchPad = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UStaticMeshComponent* HandleLaunchPad = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UPhysicsConstraintComponent* ArmConstraint = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UPhysicsConstraintComponent* WeightConstraint = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UPhysicsConstraintComponent* HandleConstraint = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UCableComponent* CableArmToWeight = nullptr;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UCableComponent* CableArmToHandle = nullptr;

	UPROPERTY()
	FTransform TransformArmSaved;

	UPROPERTY()
	FTransform TransformHandleSaved;

	UPROPERTY()
	FTransform TransformWeightSaved;

	UPROPERTY()
	ELaunchPadState LaunchPadState = ELaunchPadState::None;

	UPROPERTY(Transient)
	AZZHamsterActor* HamsterLoaded = nullptr;

	bool bBoundInteraction = false;
};

inline void AZZLaunchPad::SetLaunchPadState(ELaunchPadState InLaunchPadState)
{
	LaunchPadState = InLaunchPadState;
}
inline ELaunchPadState AZZLaunchPad::GetLaunchPadState() const
{
	return LaunchPadState;
}