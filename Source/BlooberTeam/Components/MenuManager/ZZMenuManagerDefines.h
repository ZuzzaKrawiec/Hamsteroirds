// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ZZMenuManagerDefines.generated.h"

UENUM(Blueprintable)
enum class EMenuType : uint8
{
	None,
	Main,
	Pause,
	ChangeHamster,
	Shop,
	Game
};