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
//#include "PSTTDistanceAttack.generated.h"

/*
USTRUCT()
struct FSTT_Attack_InstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	TSubclassOf<class AFPSAIProjProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Input")
	float MaxSpread = 5.0f;



	UPROPERTY(EditAnywhere, Category = "Input")
	USoundBase* FireSound = nullptr;
}; USTRUCT(meta = (DisplayName = "AI Attack Task"))
struct FPSTTDistanceAttack : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FSTT_Attack_InstanceData;

protected:

	UPROPERTY(EditAnywhere, Category = "Bindings")
	FStateTreeExternalDataHandle AIControllerHandle;

	UPROPERTY(EditAnywhere, Category = "Bindings")
	FStateTreeExternalDataHandle TargetActorHandle;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	*/

    /*
    EStateTreeRunStatus FPSTTDistanceAttack::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
    {
        const AAIController* AIController = Cast<AIController>(Context.GetOwner());
        APlayerController* PC = UGameplayStatics::GetPlayerController(Context.GetWorld(), 0);
        APawn* Player = PC ? PC->GetPawn() : nullptr;
        if (!IsValid(AIController))
        {
            return EStateTreeRunStatus::Failed;
        }

        APawn* AIPawn = AIController->GetPawn();
        if (!IsValid(AIPawn) || !IsValid(Player))
        {
            return EStateTreeRunStatus::Failed;
        }

        // Muzzle location check
        const USkeletalMeshComponent* Mesh = Cast<ACharacter>(AIPawn)->GetMesh();
        if (!Mesh || !Mesh->DoesSocketExist("Muzzle_01"))
        {
            return EStateTreeRunStatus::Failed;
        }
        const FVector MuzzleLocation = Mesh->GetSocketLocation("Muzzle_01");

        // Health check
        const UPHealthComponent* HealthComponent = Player->FindComponentByClass<UPHealthComponent>();
        if (!HealthComponent || !HealthComponent->IsPawnAlive())
        {
            return EStateTreeRunStatus::Failed;
        }

        // Calculate shot direction with spread
        FVector Direction = Player->GetActorLocation() - MuzzleLocation;
        FRotator MuzzleRotation = Direction.Rotation();

        MuzzleRotation.Pitch += FMath::RandRange(0.f, InstanceData.MaxSpread);
        MuzzleRotation.Yaw += FMath::RandRange(-InstanceData.MaxSpread, InstanceData.MaxSpread);
        Direction = MuzzleRotation.Vector();

        // Spawn projectile
        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Params.Instigator = Cast<APawn>(AIPawn);

        if (UWorld* World = AIController->GetWorld())
        {
            AFPSAIProjProjectile* Bullet = World->SpawnActor<AFPSAIProjProjectile>(
                InstanceData.ProjectileClass,
                MuzzleLocation,
                MuzzleRotation,
                Params
            );

            if (Bullet)
            {
                if (InstanceData.FireSound)
                {
                    UGameplayStatics::PlaySoundAtLocation(World, InstanceData.FireSound, MuzzleLocation);
                }

                if (UProjectileMovementComponent* ProjectileMovement = Bullet->GetProjectileMovement())
                {
                    ProjectileMovement->Velocity = Direction * ProjectileMovement->MaxSpeed;
                }
                return EStateTreeRunStatus::Succeeded;
            }
        }

        return EStateTreeRunStatus::Failed;
    }
    */