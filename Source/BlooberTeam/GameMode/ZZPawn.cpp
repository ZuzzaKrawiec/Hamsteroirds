// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ZZPawn.h"
#include "GameMode/ZZPlayerController.h"
#include "GameMode/ZZPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Hamster/ZZHamsterActor.h"
#include "Actors/Hamster/ZZHamsterData.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Camera/ZZCameraManagerComponent.h"
#include "InputAction.h"

AZZPawn::AZZPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("CameraComponent"));
	CameraComponent->bEditableWhenInherited = true;

	CameraManagerComponent = CreateDefaultSubobject<UZZCameraManagerComponent>(FName("CameraManagerComponent"));
	CameraManagerComponent->bEditableWhenInherited = true;

}

void AZZPawn::BeginPlay()
{
	Super::BeginPlay();
	//SpawnHamster();
}

void AZZPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HamsterActor)
	{
		int32 NewDistance = (HamsterActor->GetActorLocation().Y / 100.0f);
		if (NewDistance != HamsterDistance)
		{
			HamsterDistance = NewDistance;
			OnHamsterDistanceUpdate.Broadcast(HamsterDistance);
		}
	}
}

void AZZPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!PlayerEnhancedInputComponent)
	{
		return;
	}
	if (InputActionMainInteract)
	{
		PlayerEnhancedInputComponent->BindAction(InputActionMainInteract, ETriggerEvent::Started, this, &AZZPawn::UseMainInteraction);
	}
	if (InputActionRestartInteraction)
	{
		PlayerEnhancedInputComponent->BindAction(InputActionRestartInteraction, ETriggerEvent::Started, this, &AZZPawn::UseRestartInteraction);
	}
	if (InputActionPauseInteraction)
	{
		PlayerEnhancedInputComponent->BindAction(InputActionPauseInteraction, ETriggerEvent::Started, this, &AZZPawn::Pause);
	}
	if (InputActionShopInteraction)
	{
		PlayerEnhancedInputComponent->BindAction(InputActionShopInteraction, ETriggerEvent::Started, this, &AZZPawn::OpenShop);
	}
	if (InputActionChangeHamster)
	{
		PlayerEnhancedInputComponent->BindAction(InputActionChangeHamster, ETriggerEvent::Started, this, &AZZPawn::ChangeHamster);
	}
	if (InputActionUseAbility)
	{
		PlayerEnhancedInputComponent->BindAction(InputActionUseAbility, ETriggerEvent::Started, this, &AZZPawn::StartAbility);
		PlayerEnhancedInputComponent->BindAction(InputActionUseAbility, ETriggerEvent::Completed, this, &AZZPawn::StopAbility);
	}
}

void AZZPawn::PawnClientRestart()
{
	Super::PawnClientRestart();
	if (!InputMapping)
	{
		return;
	}
	AZZPlayerController* PlayerController = Cast<AZZPlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!Subsystem)
	{
		return;
	}
	Subsystem->AddMappingContext(InputMapping, 0);
}


void AZZPawn::UseRestartInteraction()
{
	if (bLockInteraction)
	{
		return;
	}
	if (!GetHamsterActor())
	{
		SpawnHamster();
		return;
	}

	if (GetHamsterActor()->GetHamsterState() == EHamsterState::PlacedOnLauncher)
	{
		return;
	}

	SpawnHamster();
}
void AZZPawn::UseMainInteraction()
{
	if (bLockInteraction)
	{
		return;
	}
	OnMainInteractionUsed.Broadcast();
}
void AZZPawn::SpawnHamster()
{
	AZZPlayerState* ZZPlayerState = Cast<AZZPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!ZZPlayerState)
	{
		return;
	}	
	UZZHamsterData* HamsterData = ZZPlayerState->GetHamsterData();
	if (!HamsterData)
	{
		return;
	}
	if (HamsterData->HamsterClass.IsNull())
	{
		return;
	}

	if (HamsterActor)
	{		
		HamsterActor->Destroy();
		HamsterActor = nullptr;
	}
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	TSubclassOf<AZZHamsterActor> HamsterClass = HamsterData->HamsterClass.LoadSynchronous();	
	HamsterActor = GetWorld()->SpawnActor<AZZHamsterActor>(HamsterClass, FTransform::Identity, Params);
	HamsterActor->OnHamsterDied.AddDynamic(this, &AZZPawn::SpawnHamster);
	OnHamasterSpawned.Broadcast(HamsterActor);
}

void AZZPawn::OpenMenuInteracton(EMenuType InMenuType)
{
	OnOpenMenuInteraction.Broadcast(InMenuType);
}
void AZZPawn::Pause()
{
	OpenMenuInteracton(EMenuType::Pause);
}
void AZZPawn::OpenShop()
{
	OpenMenuInteracton(EMenuType::Shop);
}
void AZZPawn::ChangeHamster()
{
	OpenMenuInteracton(EMenuType::ChangeHamster);
}
void AZZPawn::StartAbility()
{
	if (GetHamsterActor())
	{
		GetHamsterActor()->StartAbility();
	}
}
void AZZPawn::StopAbility()
{
	if (GetHamsterActor())
	{
		GetHamsterActor()->StopAbility();
	}
}