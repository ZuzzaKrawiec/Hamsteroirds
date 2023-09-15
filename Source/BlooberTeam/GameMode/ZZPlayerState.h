// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ZZPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHamsterDataChanged, UZZHamsterData*, InHamsterData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCashChanged, int32, InCash);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordChanged, int32, InRecord);

class AZZPawn;
class UZZPowerupManagerComponent;
class UZZHamsterData;
UCLASS()
class BLOOBERTEAM_API AZZPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AZZPlayerState();
	UZZHamsterData* GetHamsterData() const;
	void SetHamsterData(UZZHamsterData* InHamsterData);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnHamsterDataChanged OnHamsterDataChanged;

	FOnCashChanged OnCashChanged;
	int32 GetCash() const;
	void SetCash(int32 InCash);
	void AddCash(int32 Add);

	UZZPowerupManagerComponent* GetPowerupManagerComponent() const;
	FOnRecordChanged OnRecordChanged;
	UFUNCTION()
	void OnGamePawnSpawned(AZZPawn* Pawn);
	UFUNCTION()
	void OnHamsterDistanceUpdate(int32 InDistance);
protected: 
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UZZPowerupManagerComponent* PowerupManagerComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UZZHamsterData* HamsterData = nullptr;

	UPROPERTY()
	int32 Cash = 0;

	UPROPERTY()
	int32 DistanceRecord = 0;
};

inline UZZPowerupManagerComponent* AZZPlayerState::GetPowerupManagerComponent() const
{
	return PowerupManagerComponent;
}
