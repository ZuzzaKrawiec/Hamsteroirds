// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZZCameraDefines.h"
#include "ZZCameraManagerComponent.generated.h"

class AZZPawn;
class AZZHamsterActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBERTEAM_API UZZCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZZCameraManagerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CameraFollowHamster(float DeltaTime);

	UFUNCTION()
	void OnHamsterSpawned(AZZHamsterActor* InHamsterActor);
	UFUNCTION()
	void OnHamsterLaunched();
	UFUNCTION()
	void OnHamsterPlacedOnLaunch();

	FVector CalculateCameraLocation();

	ECameraState GetCameraState() const;
	void SetCameraState(ECameraState InCameraState);


protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AZZPawn* CachedPawn = nullptr;

	UPROPERTY()
	AZZHamsterActor* CurrentHamster = nullptr;

	UPROPERTY()
	ECameraState CameraState = ECameraState::WaitForLaunch;

	UPROPERTY()
	FVector LagLocation;

	UPROPERTY(EditAnywhere)
	FVector OffsetCamera = FVector(-1070.0f, 0.0f, 250.0f);

	UPROPERTY()
	float MinClampValue = 955.0f;
};

inline ECameraState UZZCameraManagerComponent::GetCameraState() const
{
	return CameraState;
}
inline void UZZCameraManagerComponent::SetCameraState(ECameraState InCameraState)
{
	CameraState = InCameraState;
}