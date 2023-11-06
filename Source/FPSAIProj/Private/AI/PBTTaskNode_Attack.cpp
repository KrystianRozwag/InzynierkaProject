// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBTTaskNode_Attack.h"

#include "AIController.h"
#include "PHealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPSAIProj/FPSAIProjProjectile.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UPBTTaskNode_Attack::UPBTTaskNode_Attack()
{
    MaxSpread = 5.f;
}

EBTNodeResult::Type UPBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

        AAIController* AIController = OwnerComp.GetAIOwner();
        if (!ensure(AIController))
        {
            return EBTNodeResult::Failed;
        }

        ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());
        if (!AIPawn)
        {
            return EBTNodeResult::Failed;
        }

        FVector MuzzleLocation;
        if (AIPawn->GetMesh() && AIPawn->GetMesh()->DoesSocketExist("Muzzle_01"))
        {
            MuzzleLocation = AIPawn->GetMesh()->GetSocketLocation("Muzzle_01");
        }
        else
        {
            return EBTNodeResult::Failed;
        }

        AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
        if (!Player)
        {
            return EBTNodeResult::Failed;
        }
        UPHealthComponent* PlayerHealthComponent = Player->FindComponentByClass<UPHealthComponent>();
        if (!PlayerHealthComponent->IsPawnAlive()) 
        {
            Player = nullptr;
            return EBTNodeResult::Failed;
        }
        FVector Direction = Player->GetActorLocation() - MuzzleLocation;
        FRotator MuzzleRotation = Direction.Rotation();
        Direction.Normalize();

        MuzzleRotation.Pitch += FMath::RandRange(0.f, MaxSpread); //added random range to give more random to AI's aim
        MuzzleRotation.Yaw += FMath::RandRange(-MaxSpread, MaxSpread);

        FActorSpawnParameters Parameters;
        Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Parameters.Instigator = AIPawn;

        AFPSAIProjProjectile* Bullet = GetWorld()->SpawnActor<AFPSAIProjProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, Parameters);

        if (FireSound)
        {
            UGameplayStatics::PlaySoundAtLocation(AIPawn, FireSound, AIPawn->GetActorLocation());
        }
	    if(Bullet)
	    {
	        Bullet->GetProjectileMovement()->Velocity = Direction * Bullet->GetProjectileMovement()->MaxSpeed;
	    }

        return Bullet ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
