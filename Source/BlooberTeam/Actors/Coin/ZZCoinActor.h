// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZZCoinActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
UCLASS()
class BLOOBERTEAM_API AZZCoinActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AZZCoinActor();

	UFUNCTION()
	void TriggerCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Collect();
	USphereComponent* GetSphereComponent() const;
protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* CoinMesh = nullptr;

};

inline USphereComponent* AZZCoinActor::GetSphereComponent() const
{
	return SphereComponent;
}
