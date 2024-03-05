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
}
