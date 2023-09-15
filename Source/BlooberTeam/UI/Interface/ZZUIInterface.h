// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "ZZUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UZZUIInterface : public UInterface
{
	GENERATED_BODY()
};

class BLOOBERTEAM_API IZZUIInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetOverrideTextStyle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FDataTableRowHandle GetTextStyleInherit();
	
};
