// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/Powerup/ZZPowerupDefines.h"
#include "ZZPowerupManagerComponent.generated.h"

class UZZPowerupData;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBERTEAM_API UZZPowerupManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZZPowerupManagerComponent();
	static bool GetPowerupStatic(UWorld* World, EPowerupIndex InPowerupIndex);
	
	void AddPowerup(EPowerupIndex InPowerupIndex);
	bool GetPowerup(EPowerupIndex InPowerupIndex);

	const TArray<TSoftObjectPtr<UZZPowerupData>>& GetPowerupsData() const;
protected:
	virtual void BeginPlay() override;

	TMap<EPowerupIndex, bool> PowerupState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UZZPowerupData>> PowerupsData;
};
