// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBTService_CheckDistanceToAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UPBTService_CheckDistanceToAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                 float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent(); //get blackboard component

	if(BBComp)
	{
		/*from blackboard component get object set as value (player) and cast to AActor (because normally it returns UObject, which does not have the location)*/
		AActor* PlayerActor = Cast<AActor>(BBComp->GetValueAsObject("Player")); 
		if(PlayerActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner(); // retrieve controller of the blackboard component
			if(AIController)
			{
				APawn* AIPawn = AIController->GetPawn(); // get the pawn used by ai controller
				if(ensure(AIPawn))
				{
					float DistanceToPlayer = FVector::Distance(PlayerActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bInRange = DistanceToPlayer < 2000.f;

					BBComp->SetValueAsBool(RangeToAttackKey.SelectedKeyName, bInRange);
				}
			}
		}
	}

}
