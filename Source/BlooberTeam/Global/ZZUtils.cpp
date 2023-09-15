// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/ZZUtils.h"
#include "Components/LocationMark/ZZLocationMarkManagerComponent.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"
#include "Components/Powerup/ZZPowerupDefines.h"


AZZGameState* UZZUtils::GetGameState(UWorld* World)
{
	if (!World)
	{
		return nullptr;
	}
	AZZGameState* Ret = Cast<AZZGameState>(UGameplayStatics::GetGameState(World));
	return Ret;
}