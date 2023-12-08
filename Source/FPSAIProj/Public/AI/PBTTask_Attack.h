// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class FPSAIPROJ_API UPBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USoundBase* FireSound;
	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category="AI")
	float MaxSpread;

public:
	UPBTTask_Attack();
};
