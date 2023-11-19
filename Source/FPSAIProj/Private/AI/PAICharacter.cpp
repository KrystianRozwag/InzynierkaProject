// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "PHealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSAIProj/FPSAIProjGameMode.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
APAICharacter::APAICharacter()
{

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	HealthComponent = CreateDefaultSubobject<UPHealthComponent>("HealthComponent");

	TimeOfHitParamName = "TimeOfHit";
}

void APAICharacter::PostInitializeComponents()
{

	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &APAICharacter::OnPawnSeen); //binding method OnPawnSeen to OnSeePawn delegate so it executes when ai sees a pawn
	HealthComponent->OnHealthChanged.AddDynamic(this, &APAICharacter::OnHealthChanged); //binding dynamic to OnHealthChanged in HealthComponent so it might be decreased when hit
}

//method to get player if seen (by using dynamic delegate to PawnSensingComponent method) and set its pawn as new value in blackboard component
void APAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject("Player", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "Player seen", nullptr, FColor::Red, 4.0f, true);
	}
}

void APAICharacter::OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth,
	float Delta)
{
	if(Delta < 0.f)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if(InstigatorActor != this)
		{
			if (AIController)
			{
				AIController->GetBlackboardComponent()->SetValueAsObject("Player", InstigatorActor); //if hit by player set value in blackboard so it immediately detects and turns toward the player
			}
		}

		if(NewHealth <= 0.f)
		{
			if(AIController)
			{
				AIController->GetBrainComponent()->StopLogic("Dead"); // stopping the BT because AI is dead
			}
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
