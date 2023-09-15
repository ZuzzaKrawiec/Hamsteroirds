// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "Styling/SlateTypes.h"
#include "ZZButtonDefines.generated.h"

USTRUCT(Blueprintable)
struct FButtonsStylesData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FButtonStyle ButtonStyle;
};