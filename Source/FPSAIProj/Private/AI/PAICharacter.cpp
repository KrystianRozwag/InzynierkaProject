// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
APAICharacter::APAICharacter()
{

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

}

void APAICharacter::PostInitializeComponents()
{

	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &APAICharacter::OnPawnSeen); //binding object and OnPawnSeen to OnSeePawn delegate
}
//method to get player if seen (by using dynamic delegate to PawnSensingComponent method) and set its pawn as new value in blackboard component
void APAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());

	if(AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

		BlackboardComponent->SetValueAsObject("Player", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "Player seen", nullptr, FColor::Red, 4.0f, true);
	}
}
