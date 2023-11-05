// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBTService_CheckCritHealth.h"

#include <string>

#include "AIController.h"
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
			if (HealthComponent->GetHealth() < LowHealth) { 
				bool bLowHealth = (HealthComponent->GetHealth() / HealthComponent->GetHealthMax() < LowHealth/100); // checking if health/max health is smaller than 40%
				UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
				BlackboardComponent->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
			}
		}
	}
}
