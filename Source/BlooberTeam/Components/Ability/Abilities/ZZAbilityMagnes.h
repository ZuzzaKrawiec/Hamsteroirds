// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Ability/ZZAbilityHamsterComponent.h"
#include "ZZAbilityMagnes.generated.h"

class USphereComponent;
class UPrimitiveComponent;
UCLASS(Blueprintable, Blueprinttype, meta = (BlueprintSpawnableComponent))
class BLOOBERTEAM_API UZZAbilityMagnes : public UZZAbilityHamsterComponent
{
	GENERATED_BODY()
public:
	virtual void TriggerPowerDuration(float DeltaTime) override;
	virtual void StartPower() override;
	virtual void StopPower() override;

	UFUNCTION()
	void AddCoinToArray(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void AddCoin(UPrimitiveComponent* CoinRoot);
protected:
	UPROPERTY()
	USphereComponent* MagnesSphere;

	UPROPERTY()
	TArray<UPrimitiveComponent*> CoinsArray;
};
