// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/MenuManager/ZZMenuManagerDefines.h"
#include "ZZPawn.generated.h"

class UInputAction;
class UInputMappingContext;
class AZZHamsterActor;
class UCameraComponent;
class UZZCameraManagerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMainInteractionUsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestartUsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenMenuInteraction, EMenuType, InMenuType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHamasterSpawned, AZZHamsterActor*, InHamsterActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHamsterDistanceUpdate, int32, Distance);

UCLASS()
class BLOOBERTEAM_API AZZPawn : public APawn
{
	GENERATED_BODY()

public:
	AZZPawn();

	void UseRestartInteraction();
	void UseMainInteraction();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnHamster();

	/*When new hamster is spawned*/
	FOnHamasterSpawned OnHamasterSpawned;
	/*when space or lpm is pressed*/
	FOnMainInteractionUsed OnMainInteractionUsed;
	FOnRestartUsed OnRestartUsed;
	FOnHamsterDistanceUpdate OnHamsterDistanceUpdate;

	void OpenMenuInteracton(EMenuType InMenuType);
	FOnOpenMenuInteraction OnOpenMenuInteraction;
	/*Inputs*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction* InputActionMainInteract;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction* InputActionRestartInteraction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction* InputActionPauseInteraction;
	UFUNCTION()
	void Pause();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction* InputActionShopInteraction;
	UFUNCTION()
	void OpenShop();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction* InputActionChangeHamster;
	UFUNCTION()
	void ChangeHamster();


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction* InputActionUseAbility;
	void StartAbility();
	void StopAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputMappingContext* InputMapping;

	AZZHamsterActor* GetHamsterActor() const;
	void SetHamsterActor(AZZHamsterActor* InHamsterActor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UZZCameraManagerComponent* GetCameraManagerComponent() const;

	
	bool GetLockInteraction() const;
	void SetLockInteraction(bool bState);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	UZZCameraManagerComponent* CameraManagerComponent = nullptr;

	UPROPERTY()
	AZZHamsterActor* HamsterActor = nullptr;

	UPROPERTY()
	int32 HamsterDistance = 0.0f;

	UPROPERTY()
		bool bLockInteraction = false;
};

inline AZZHamsterActor* AZZPawn::GetHamsterActor() const
{
	return HamsterActor;
}
inline void AZZPawn::SetHamsterActor(AZZHamsterActor* InHamsterActor)
{
	HamsterActor = InHamsterActor;
}
inline UZZCameraManagerComponent* AZZPawn::GetCameraManagerComponent() const
{
	return CameraManagerComponent;
}
inline bool AZZPawn::GetLockInteraction() const
{
	return bLockInteraction;
}
inline void AZZPawn::SetLockInteraction(bool bState)
{
	bLockInteraction = bState;
}