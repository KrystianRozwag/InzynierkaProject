// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBTService_CheckCritHealth.h"

#include <string>

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "PHealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UPBTService_CheckCritHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(AIPawn)
	{
		UPHealthComponent* HealthComponent = AIPawn->FindComponentByClass<UPHealthComponent>();
		DrawDebugString(GetWorld(), AIPawn->GetActorLocation(),FString::SanitizeFloat(HealthComponent->GetHealth()), 0, FColor::Green, 2.0f, false, 1);
		if(HealthComponent)
		{
			SetLowHealthInBlackboard(OwnerComp, HealthComponent);
		}
	}
}
// Function to check and set low health in the Blackboard
void UPBTService_CheckCritHealth::SetLowHealthInBlackboard(UBehaviorTreeComponent& OwnerComp, UPHealthComponent* HealthComponent) const
{
	const float HealthPercentage = HealthComponent->GetHealth() / HealthComponent->GetHealthMax();
	if (HealthPercentage <= LowHealth / 100.0f)
	{
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsBool(LowHealthKey.SelectedKeyName, true);
		}
	}
}
