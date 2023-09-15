// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZZLocationMarkDefines.h"
#include "ZZLocationMarkManagerComponent.generated.h"

#define MARKSTART FName("Start")

class AZZLocationMarkActor;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBERTEAM_API UZZLocationMarkManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	static bool MoveToMarker(UWorld* World, AActor* Actor, const FName& MarkerName);

	UZZLocationMarkManagerComponent();

	void RegisterLocationMark(AZZLocationMarkActor* LocationMark);
	const FTransform& GetMarkTransform(const FName& Name);
protected:
	UPROPERTY()
	TMap<FName, FLocationMarkData> Markers;


	
};
