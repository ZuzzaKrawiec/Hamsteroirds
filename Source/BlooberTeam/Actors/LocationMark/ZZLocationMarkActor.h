// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "ZZLocationMarkActor.generated.h"

UCLASS()
class BLOOBERTEAM_API AZZLocationMarkActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AZZLocationMarkActor();

	inline const FName& GetMarkName() const
	{
		return MarkName;
	};

protected:
	virtual void BeginPlay() override;
	void RegisterLocationMark();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName MarkName;

	UPROPERTY( BlueprintReadOnly)
	UArrowComponent* ArrowComponent = nullptr;
};
