// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Coin/ZZCoinActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameMode/ZZPlayerState.h"
#include "Kismet/GameplayStatics.h"

AZZCoinActor::AZZCoinActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));
	SphereComponent->bEditableWhenInherited = true;
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CoinMesh"));
	CoinMesh->bEditableWhenInherited = true;

	RootComponent = SphereComponent;
	CoinMesh->SetupAttachment(SphereComponent);
}

void AZZCoinActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AZZCoinActor::TriggerCollect);
}
void AZZCoinActor::TriggerCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherComp->GetCollisionObjectType() != ECC_Pawn)
	{
		return;
	}
	Collect();
	Destroy();
}
void AZZCoinActor::Collect()
{
	AZZPlayerState* PlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!PlayerState)
	{
		return;
	}

	PlayerState->AddCash(1);

}