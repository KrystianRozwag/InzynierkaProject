// Fill out your copyright notice in the Description page of Project Settings.


#include "PAction_SecondaryAttack.h"

#include "FPSAIProj/FPSAIProjCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UPAction_SecondaryAttack::UPAction_SecondaryAttack()
{
	AttackAnimDelay = 0.2f;
	//HandSocketName = "hand_r";
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}
void UPAction_SecondaryAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	AFPSAIProjCharacter* Character = Cast<AFPSAIProjCharacter>(Instigator);
	if(Character)
	{
		//Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}


	
}

void UPAction_SecondaryAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)

{
	UWorld* const World = GetWorld(); //TODO fixing projectile spawning
	if (InstigatorCharacter == nullptr || InstigatorCharacter->GetController() == nullptr)
	{
		return;
	}
	if(ensureAlways(ProjectileClass) && World)
	{
		/*
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();

		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000);

		FHitResult Hit;

		if(GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);*/
		APlayerController* PlayerController = Cast<APlayerController>(InstigatorCharacter->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = InstigatorCharacter->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;
		// Ignore Player
		//FCollisionQueryParams Params;
		//Params.AddIgnoredActor(Character);

	//	World->SpawnActor<AFPSAIProjProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		FTransform SpawnTM = FTransform(SpawnRotation, SpawnLocation); //was spawnrotation, checking if proj rotation works
		World->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = InstigatorCharacter->GetMesh()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
	StopAction(InstigatorCharacter);
}

