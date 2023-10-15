// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void APAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree); //running the behavior tree set in the editor


	APawn* MyPawn =  UGameplayStatics::GetPlayerPawn(this, 0); //getting player pawn to obtain location
	if(MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("LocationToPlayer", MyPawn->GetActorLocation()); // setting blackboard's component exposed in the editor to pawn's location (BB key was named LocationToPlayer)

		GetBlackboardComponent()->SetValueAsObject("Player", MyPawn); // setting object in BB to player's pawn
	}
}
