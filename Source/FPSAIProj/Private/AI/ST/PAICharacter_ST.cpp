// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ST/PAICharacter_ST.h"


#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSAIProj/FPSAIProjGameMode.h"
#include "Perception/AIPerceptionComponent.h"
#include "PHealthComponent.h"
#include "GameplayStateTreeModule/Public/Components/StateTreeComponent.h"
// Sets default values
APAICharacter_ST::APAICharacter_ST()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>("StateTreeComponent");
}

void APAICharacter_ST::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//HealthComponent->OnHealthChanged.AddDynamic(this, &APAICharacter_ST::OnHealthChanged);
}

void APAICharacter_ST::OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth,
                                        float Delta)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (Delta < 0.f && AIController)
	{

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

