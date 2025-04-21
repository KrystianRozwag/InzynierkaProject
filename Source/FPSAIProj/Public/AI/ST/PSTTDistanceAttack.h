// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeNodeBlueprintBase.h"
#include "StateTreeTaskBase.h"
#include "StateTreeExecutionContext.h"
#include "PSTTDistanceAttack.generated.h"

class E_ActionType;
USTRUCT()
struct FMyInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Input)
    AActor* AIPawn;
    //UPROPERTY(EditAnywhere, Category = Parameter)
    //E_ActionType* AnimationType;
    UPROPERTY(EditAnywhere, Category = Parameter)
    float CriticalHealth;

    UPROPERTY(EditAnywhere, Category = Parameter)
    TObjectPtr<UAnimMontage> MontageToPlay;

    UPROPERTY(EditAnywhere, Category = Parameter)
    TSubclassOf<AActor> ProjectileClass;

};

USTRUCT(meta = (DisplayName = "ST Distance Task"))
struct FPSTTDistanceAttack : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FMyInstanceData;

    virtual const UStruct* GetInstanceDataType() const override
    {
        return FMyInstanceData::StaticStruct();
    }

    UPROPERTY(EditAnywhere, Category = "Input")
    float PlayRate = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Bindings")
    FStateTreeExternalDataHandle AIControllerHandle;

    UPROPERTY(EditAnywhere, Category = "Bindings")
    FStateTreeExternalDataHandle PlayerHandle;

    virtual EStateTreeRunStatus EnterState(
        FStateTreeExecutionContext& Context,
        const FStateTreeTransitionResult& Transition) const override;

private:
    mutable FOnMontageEnded MontageEndedDelegate;
};

