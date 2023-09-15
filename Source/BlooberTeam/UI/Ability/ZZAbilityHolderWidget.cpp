// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ability/ZZAbilityHolderWidget.h"
#include "GameMode/ZZPawn.h"
#include "Components/Ability/ZZAbilityHamsterComponent.h"
#include "UI/Ability/ZZAbilityWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Hamster/ZZHamsterActor.h"


void UZZAbilityHolderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AZZPawn* Pawn = Cast<AZZPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Pawn)
	{
		return;
	}
	if (Pawn->GetHamsterActor())
	{
		OnHamsterSpawned(Pawn->GetHamsterActor());
	}
	Pawn->OnHamasterSpawned.AddDynamic(this, &UZZAbilityHolderWidget::OnHamsterSpawned);
}
void UZZAbilityHolderWidget::OnHamsterSpawned(AZZHamsterActor* InHamsterActor)
{
	for (UZZAbilityWidget* AbilityWidget : AbilityArray)
	{
		AbilityWidget->RemoveFromParent();
	}
	AbilityArray.Empty();

	if (!InHamsterActor)
	{
		return;
	}

	TArray<UActorComponent*> OutComponents;
	InHamsterActor->GetComponents(OutComponents, false);
	for (UActorComponent* Component : OutComponents)
	{
		UZZAbilityHamsterComponent* Ability = Cast<UZZAbilityHamsterComponent>(Component);
		if (!Ability)
		{
			continue;
		}

		if (Ability->AbilityWidgetClass.IsNull())
		{
			continue;;
		}

		UZZAbilityWidget* AbilityWidget = Cast<UZZAbilityWidget>(CreateWidget(GetOwningPlayer(), Ability->AbilityWidgetClass.LoadSynchronous()));
		if (!AbilityWidget)
		{
			continue;
		}
		AbilitiesBox->AddChildToHorizontalBox(AbilityWidget);
		AbilityWidget->SetData(Ability);
		AbilityArray.Add(AbilityWidget);
	}
}