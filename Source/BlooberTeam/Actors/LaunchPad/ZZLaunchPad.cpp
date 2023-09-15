// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LaunchPad/ZZLaunchPad.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameMode/ZZPawn.h"
#include "GameMode/ZZPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "CableComponent/Classes/CableComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/Powerup/ZZPowerupManagerComponent.h"

AZZLaunchPad::AZZLaunchPad()
{
	PrimaryActorTick.bCanEverTick = true;
	JetLaunchPad = CreateDefaultSubobject<USkeletalMeshComponent>(FName("JetLaunchPad"));
	JetLaunchPad->bEditableWhenInherited = true;

	ArmLaunchPad = CreateDefaultSubobject<UStaticMeshComponent>(FName("ArmLaunchPad"));
	ArmLaunchPad->bEditableWhenInherited = true;

	WeightLaunchPad = CreateDefaultSubobject<UStaticMeshComponent>(FName("WeightLaunchPad"));
	WeightLaunchPad->bEditableWhenInherited = true;

	HandleLaunchPad = CreateDefaultSubobject<UStaticMeshComponent>(FName("HandleLaunchPad"));
	HandleLaunchPad->bEditableWhenInherited = true;
	
	ArmConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("ArmConstraint"));
	WeightConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WeightConstraint"));
	HandleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("HandleConstraint"));
	CableArmToWeight = CreateDefaultSubobject<UCableComponent>(FName("ArmToWeight"));
	CableArmToHandle = CreateDefaultSubobject<UCableComponent>(FName("ArmToHamster"));

	RootComponent = JetLaunchPad;
	ArmLaunchPad->SetupAttachment(JetLaunchPad);
	ArmConstraint->SetupAttachment(JetLaunchPad);
	WeightLaunchPad->SetupAttachment(JetLaunchPad);
	HandleLaunchPad->SetupAttachment(JetLaunchPad);
	WeightConstraint->SetupAttachment(JetLaunchPad);
	HandleConstraint->SetupAttachment(JetLaunchPad);
	CableArmToWeight->SetupAttachment(ArmLaunchPad);
	CableArmToHandle->SetupAttachment(ArmLaunchPad);
}

void AZZLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	SaveStartingState();
	WaitForPawn();
}

void AZZLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AZZLaunchPad::SaveStartingState()
{
	TransformHandleSaved = HandleLaunchPad->GetComponentTransform();
	TransformWeightSaved = WeightLaunchPad->GetComponentTransform();
	TransformArmSaved = ArmLaunchPad->GetComponentTransform();
}
void AZZLaunchPad::RestoreStartingState()
{
	if (UZZPowerupManagerComponent::GetPowerupStatic(GetWorld(), EPowerupIndex::Counterweight))
	{
		WeightLaunchPad->SetMassOverrideInKg(NAME_None, 5000.0f, true);
	}
	HandleLaunchPad->SetLinearDamping(0.01f);
	HandleLaunchPad->SetAngularDamping(0.0f);
	LaunchPadSimulation(false);
	HandleLaunchPad->SetWorldTransform(TransformHandleSaved);
	WeightLaunchPad->SetWorldTransform(TransformWeightSaved);
	ArmLaunchPad->SetWorldTransform(TransformArmSaved);
	CableArmToHandle->SetAttachEndToComponent(HandleLaunchPad);
	HandleConstraint->InitComponentConstraint();
	CableArmToHandle->bAttachEnd = true;
}


void AZZLaunchPad::LaunchPadSimulation(bool bState)
{
	HandleLaunchPad->SetSimulatePhysics(bState);
	WeightLaunchPad->SetSimulatePhysics(bState);
	ArmLaunchPad->SetSimulatePhysics(bState);
}

void AZZLaunchPad::ReleaseHamster()
{
	HandleLaunchPad->SetAngularDamping(25.0f);
	HandleLaunchPad->SetLinearDamping(5.0f);
	HandleConstraint->BreakConstraint();
	if (HamsterLoaded)
	{
		CableArmToHandle->bAttachEnd = false;
		FVector Velocity = FVector::ZeroVector;
		HandleLaunchPad->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Velocity = HandleLaunchPad->GetComponentVelocity();
		HamsterLoaded->StartFlying(Velocity);		
	}

	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	Pawn->OnMainInteractionUsed.RemoveDynamic(this, &AZZLaunchPad::TriggerLaunchPadBehavior);
	bBoundInteraction = false;
}

void AZZLaunchPad::PlaceHamster(AZZHamsterActor* InHamsterActor)
{
	if (!InHamsterActor)
	{
		return;
	}
	RestoreStartingState();
	HamsterLoaded = InHamsterActor;
	HamsterLoaded->SetActorEnableCollision(false);
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	HamsterLoaded->AttachToComponent(HandleLaunchPad, AttachmentTransformRules);
	SetLaunchPadState(ELaunchPadState::Loaded);
	HamsterLoaded->PlacedOnLaunch();

	if (!bBoundInteraction)
	{
		AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (!Pawn)
		{
			return;
		}
		Pawn->OnMainInteractionUsed.AddDynamic(this, &AZZLaunchPad::TriggerLaunchPadBehavior);
		bBoundInteraction = true;
	}
}
void AZZLaunchPad::TriggerLaunchPadBehavior()
{
	switch (LaunchPadState)
	{
		case ELaunchPadState::Loaded:
		{
			LaunchPadSimulation(true);
			SetLaunchPadState(ELaunchPadState::Simulating);
			break;
		}
		case ELaunchPadState::Simulating:
		{
			ReleaseHamster();
			SetLaunchPadState(ELaunchPadState::Fired);
			break;
		}
		case ELaunchPadState::Fired:
		{
			// we wait till hamster is stopped then reset launch pad
			break;
		}
	}
}
void AZZLaunchPad::BindBehavior(AZZPawn* InPawn)
{
	if (!InPawn)
	{
		return;
	}
	if (InPawn->GetHamsterActor())
	{
		//Hamster already exist and this is first attachemtn
		PlaceHamster(InPawn->GetHamsterActor());
	}
	InPawn->OnHamasterSpawned.AddDynamic(this, &AZZLaunchPad::PlaceHamster);
}
void AZZLaunchPad::WaitForPawn()
{
	AZZPlayerController* PlayerController = Cast<AZZPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController)
	{
		return;
	}
	PlayerController->OnGamePawnSpawned.AddDynamic(this, &AZZLaunchPad::BindBehavior);
}