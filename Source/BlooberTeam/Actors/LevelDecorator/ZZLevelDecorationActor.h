// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZZLevelDecorationActor.generated.h"

class UZZDecorationData;
UCLASS()
class BLOOBERTEAM_API AZZLevelDecorationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AZZLevelDecorationActor();

	void SetData(UZZDecorationData* TextureDecrotaion);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh = nullptr;
};
