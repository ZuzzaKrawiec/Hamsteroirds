// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "ZZTrebuchet.generated.h"

UCLASS()
class BLOOBERTEAM_API AZZTrebuchet : public AActor
{
	GENERATED_BODY()
	
public:	
	AZZTrebuchet();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* TrebuchetBase;


};
