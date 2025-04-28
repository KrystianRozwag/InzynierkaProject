// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ST/PSTTDistanceAttack.h"

#include "AIController.h"
#include "PHealthComponent.h"
#include "FPSAIProj/FPSAIProjProjectile.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
EStateTreeRunStatus FPSTTDistanceAttack::EnterState(FStateTreeExecutionContext& Context,
                                                    const FStateTreeTransitionResult& Transition) const
{
        FInstanceDataType& InstanceData = Context.GetInstanceData(*this);


        // Get AI Pawn from controller
        APawn* AIPawn = Cast<APawn>(InstanceData.AIPawn);
        UAnimMontage* Montage = Cast<UAnimMontage>(InstanceData.MontageToPlay);
        if (!IsValid(AIPawn))
        {
            return EStateTreeRunStatus::Failed;
        }

        UWorld* World = Context.GetWorld(); // Requires UE 5.3+
        if (!World)
        {
            return EStateTreeRunStatus::Failed;
        }

        AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(World, 0));
        if (!IsValid(Player))
        {
            return EStateTreeRunStatus::Failed;
        }

        const USkeletalMeshComponent* Mesh = Cast<ACharacter>(AIPawn)->GetMesh();
        if (!Mesh || !Mesh->DoesSocketExist("hand_r"))
        {
            return EStateTreeRunStatus::Failed;
        }

        const TArray<USceneComponent*>& Children = Mesh->GetAttachChildren();
        FVector MuzzleLocation;
        for (USceneComponent* Child : Children)
        {
            USkeletalMeshComponent* AttachedSkeletalMesh = Cast<USkeletalMeshComponent>(Child);
            if (AttachedSkeletalMesh)
            {
                MuzzleLocation = AttachedSkeletalMesh->GetSocketLocation("Bow6");
                if (MuzzleLocation != FVector(0, 0, 0)) {
                    break;
                }

            }
        }
       // const FVector MuzzleLocation = Mesh->GetSocketLocation("hand_r");

        // Health check
        UPHealthComponent* HealthComponent = Player->FindComponentByClass<UPHealthComponent>();
        if (!HealthComponent || !HealthComponent->IsPawnAlive())
        {
            return EStateTreeRunStatus::Failed;
        }

        // Calculate shot direction with spread
        FVector Direction = Player->GetActorLocation() - MuzzleLocation;
        FRotator MuzzleRotation = Direction.Rotation();

        MuzzleRotation.Pitch += FMath::RandRange(0.f, 1.f);
        MuzzleRotation.Yaw += FMath::RandRange(-1.f, 1.f);
        Direction = MuzzleRotation.Vector();
        FVector AdjustedLocation = MuzzleLocation + (MuzzleRotation.Vector() * 50.0f);
        // Spawn projectile

        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Params.Instigator = AIPawn;

        UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
        
        if (World)
        {
            AFPSAIProjProjectile* Bullet = World->SpawnActor<AFPSAIProjProjectile>(
                InstanceData.ProjectileClass,
                AdjustedLocation,
                MuzzleRotation, 
                Params
            );

            if (Bullet)
            {
              //  if (InstanceData.FireSound)
            //    {
            // //       UGameplayStatics::PlaySoundAtLocation(World, InstanceData.FireSound, MuzzleLocation);
             //   }
                UProjectileMovementComponent* ProjectileMovement = Bullet->GetProjectileMovement();
                ProjectileMovement->Velocity = Direction * ProjectileMovement->MaxSpeed;

                
                return EStateTreeRunStatus::Succeeded;
            }
        }

        return EStateTreeRunStatus::Failed;
    
    }

