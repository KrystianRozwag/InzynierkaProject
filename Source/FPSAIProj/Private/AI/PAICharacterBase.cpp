// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PAICharacterBase.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "PHealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSAIProj/FPSAIProjGameMode.h"
// Sets default values
APAICharacterBase::APAICharacterBase()
{
	HealthComponent = CreateDefaultSubobject<UPHealthComponent>("HealthComponent");

	TimeOfHitParamName = "TimeOfHit";
}

void APAICharacterBase::PostInitializeComponents()
{

	Super::PostInitializeComponents();
	
	HealthComponent->OnHealthChanged.AddDynamic(this, &APAICharacterBase::OnHealthChanged); //binding dynamic to OnHealthChanged in HealthComponent so it might be decreased when hit
}

void APAICharacterBase::OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth,
	float Delta)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (Delta < 0.f && AIController)
	{

		if (InstigatorActor != this)
		{
			AIController->GetBlackboardComponent()->SetValueAsObject("Player", InstigatorActor); //if hit by player set value in blackboard so it immediately detects and turns toward the player
		}

		if (NewHealth <= 0.f)
		{
			AIController->GetBrainComponent()->StopLogic("Dead"); // stopping the BT because AI is dead

			AFPSAIProjGameMode* GameMode = GetWorld()->GetAuthGameMode<AFPSAIProjGameMode>();
			if (GameMode)
			{
				GameMode->OnActorKilled(GetOwner(), InstigatorActor);
			}
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetCapsuleComponent()->SetCollisionProfileName("NoCollision");

			SetLifeSpan(5.f);
		}
	}
}

