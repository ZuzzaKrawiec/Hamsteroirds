// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ZZPowerupDefines.generated.h"

UENUM()
enum class EPowerupIndex : uint8
{
	ImpulseJump,
	LessFriction,
	Counterweight,
	MoreCoins,
	Trampolines,
	BaseAbility
};