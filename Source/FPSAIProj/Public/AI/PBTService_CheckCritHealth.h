// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PBTService_CheckCritHealth.generated.h"

class UPHealthComponent;
/**
 * 
 */
UCLASS()
class FPSAIPROJ_API UPBTService_CheckCritHealth : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealth = 40.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector LowHealthKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void SetLowHealthInBlackboard(UBehaviorTreeComponent& OwnerComp, UPHealthComponent* HealthComponent) const;
};
