// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ZZHUD.h"
#include "Components/MenuManager/ZZMenuManagerComponent.h"

AZZHUD::AZZHUD()
{
	MenuManagerComponent = CreateDefaultSubobject<UZZMenuManagerComponent>(FName("Menu Manager Component"));
	MenuManagerComponent->bEditableWhenInherited = true;
}