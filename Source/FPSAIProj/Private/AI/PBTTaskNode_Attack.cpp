// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBTTaskNode_Attack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPSAIProj/FPSAIProjProjectile.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UPBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());
		if(AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = AIPawn->GetMesh()->GetSocketLocation("Muzzle_01"); //get muzzle location from ai's rifle

		AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player")); //get player from blackboard component value
		if(Player == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = Player->GetActorLocation() - MuzzleLocation; //vector between actor location and AI's rifle's muzzle location so it points to player
		FRotator MuzzleRotation = Direction.Rotation(); //setting rotation of the muzzle from Direction vector

		FActorSpawnParameters Parameters;
		Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //collision parameter for bullet

		AActor* Bullet = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Parameters); //spawn projectile (bullet)

		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, AIPawn->GetActorLocation());
		}

		return Bullet ? EBTNodeResult::Succeeded : EBTNodeResult::Failed; //if bullet hit the player, then succeeded
	}
	return EBTNodeResult::Failed;
}
