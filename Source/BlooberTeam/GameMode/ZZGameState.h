// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ZZGameState.generated.h"

class UZZLevelStreamerManagerComponent;
class AZZLaunchPad;
class UZZLocationMarkManagerComponent;
DECLARE_DELEGATE(FOnStartWorldLoaded)
/**
 * 
 */
UCLASS()
class BLOOBERTEAM_API AZZGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AZZGameState();


	void StartMenu();
	void StartGame(FOnStartWorldLoaded OnStartWorldLoaded);
	UFUNCTION()
	void StartWorldLoaded();

	void FirstGameStart();

	UZZLocationMarkManagerComponent* GetLocationMarkManagerComponent() const;

protected:
	virtual void BeginPlay() override;	

	FOnStartWorldLoaded OnStartWorldLoaded;

	bool bGamePrepared = false;

	UPROPERTY(BlueprintReadOnly)
	AZZLaunchPad* LaunchPad = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UZZLevelStreamerManagerComponent* LevelStreamerManagerComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UZZLocationMarkManagerComponent* LocationMarkManagerComponent = nullptr;

};
inline UZZLocationMarkManagerComponent* AZZGameState::GetLocationMarkManagerComponent() const
{
	return LocationMarkManagerComponent;
}