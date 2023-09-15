// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ZZCameraDefines.generated.h"

UENUM()
enum class ECameraState : uint8
{
	WaitForBeingPlacedOnLaunch,
	WaitForLaunch,
	FollowingHamster
};