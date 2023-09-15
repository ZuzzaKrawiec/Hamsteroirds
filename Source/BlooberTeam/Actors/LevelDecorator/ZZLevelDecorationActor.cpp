// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelDecorator/ZZLevelDecorationActor.h"
#include "Actors/LevelDecorator/ZZDecorationData.h"
#include "Kismet/KismetMathLibrary.h"


AZZLevelDecorationActor::AZZLevelDecorationActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DecorationPlane"));
	StaticMesh->bEditableWhenInherited = true;

	RootComponent = StaticMesh;
}
void AZZLevelDecorationActor::SetData(UZZDecorationData* TextureDecrotaion)
{
	if (!TextureDecrotaion)
	{
		return;
	}
	StaticMesh->SetMaterial(0, TextureDecrotaion->Material);
	StaticMesh->SetDefaultCustomPrimitiveDataFloat(0, UKismetMathLibrary::RandomInteger(TextureDecrotaion->MaxGridIndex));
}