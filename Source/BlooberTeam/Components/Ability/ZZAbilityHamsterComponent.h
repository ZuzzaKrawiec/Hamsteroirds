// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZZAbilityHamsterComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDurabilityChanged, float, InCurrentDurability, float, InMaxDurability);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReadyChanged, bool, bInIsReady);

class UZZAbilityWidget;
class AZZHamsterActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBERTEAM_API UZZAbilityHamsterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZZAbilityHamsterComponent();

	virtual void StartPower();
	virtual void StopPower();
	virtual void TriggerPower();
	virtual bool IsReady();
	void CoolDownReset();
	virtual void Refil();
	virtual void ConsumeDuration(float DeltaTime);
	virtual void TriggerPowerDuration(float DeltaTime);

	void RefillTick();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UZZAbilityWidget> AbilityWidgetClass;

	FOnDurabilityChanged OnDurabilityChanged;
	FOnReadyChanged OnReadyChanged;

	bool GetHasDurability() ;

	void SetCurrentDurability(float InDurability);
	void SetIsReady(bool bInIsReady);
	virtual float GetCoolDownTime();
	virtual float GetRefillPower();
	virtual float GetDelayRefill();
protected:
	virtual void BeginPlay() override;


	bool bIsUsing = false;
	/*Is this power can be used for */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHasDurability = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHasDurability"))
	float MaxDurability = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHasDurability"))
	float CurrentDurability = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHasDurability"))
	float ConsumeDurability = 25.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHasDurability"))
	float DelayRefill = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bHasDurability"))
	float RefillPower = 1.0f;
	FTimerHandle DelayRefillTimer;

	bool bIsReady = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CoolDownTime = 2.0f;
	UPROPERTY()
	FTimerHandle CoolDownTimer;
	UPROPERTY()
	AZZHamsterActor* Hamster = nullptr;

	bool bHasBonus = false;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};


inline bool UZZAbilityHamsterComponent::GetHasDurability()
{
	return bHasDurability;
}
inline float UZZAbilityHamsterComponent::GetCoolDownTime()
{
	return CoolDownTime;
}
inline float UZZAbilityHamsterComponent::GetRefillPower()
{
	return RefillPower;
}
inline float UZZAbilityHamsterComponent::GetDelayRefill()
{
	return DelayRefill;
}
