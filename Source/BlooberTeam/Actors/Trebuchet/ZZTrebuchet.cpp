// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Trebuchet/ZZTrebuchet.h"

AZZTrebuchet::AZZTrebuchet()
{
	PrimaryActorTick.bCanEverTick = true;

	TrebuchetBase = CreateDefaultSubobject<UStaticMeshComponent>(FName("TrebuchetBase"));
	TrebuchetBase->bEditableWhenInherited = true;

	TrebuchetBase->SetupAttachment(RootComponent);
}

void AZZTrebuchet::BeginPlay()
{
	Super::BeginPlay();
	
}
void AZZTrebuchet::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}