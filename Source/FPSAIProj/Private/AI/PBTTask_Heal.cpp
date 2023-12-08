// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBTTask_Heal.h"
#include <PHealthComponent.h>
#include "AIController.h"
EBTNodeResult::Type UPBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UPHealthComponent* HealthComponent = AIPawn->FindComponentByClass<UPHealthComponent>();
	if(HealthComponent)
	{
		HealthComponent->ApplyHealthChange(AIPawn, HealthComponent->GetHealthMax());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
