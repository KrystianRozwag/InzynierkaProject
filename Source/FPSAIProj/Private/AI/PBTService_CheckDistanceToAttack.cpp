// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBTService_CheckDistanceToAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UPBTService_CheckDistanceToAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                 float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* BBComponent = OwnerComp.GetBlackboardComponent(); // Get the Blackboard component

    if (!BBComponent)
    {
        return;
    }

    AActor* PlayerActor = Cast<AActor>(BBComponent->GetValueAsObject("Player")); // Get the player from the Blackboard

    if (!PlayerActor)
    {
        return;
    }

    AAIController* AIController = OwnerComp.GetAIOwner(); // Get the AI controller

    if (!AIController)
    {
        return;
    }

    APawn* AIPawn = AIController->GetPawn(); // Get the pawn used by the AI controller

    if (!ensure(AIPawn))
    {
        return;
    }

    float DistanceToPlayer = FVector::Distance(PlayerActor->GetActorLocation(), AIPawn->GetActorLocation());
    bool bInRange = DistanceToPlayer < MinDistanceToPlayer; // Check if the player is within the minimum distance
    bool bHasLOSToPlayer = false;

    if (bInRange)
    {
        bHasLOSToPlayer = AIController->LineOfSightTo(PlayerActor); // Check if the player is visible to AI
    }

    // Set the Blackboard value based on range and line of sight to the player
    BBComponent->SetValueAsBool(RangeToAttackKey.SelectedKeyName, (bInRange && bHasLOSToPlayer));



}
