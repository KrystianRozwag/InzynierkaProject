// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSAIProjProjectile.h"

#include "PHealthComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AFPSAIProjProjectile::AFPSAIProjProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSAIProjProjectile::OnHit);		// set up a notification for when this component hits something blocking
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSAIProjProjectile::OnActorOverlap); //if collision component is overlapped code runs OnActorOverlap to add/sub health
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;


	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetRelativeLocation(FVector::ZeroVector);
	AudioComponent->Play();

	DamageAmount = 20.0f;
}

void AFPSAIProjProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

}
//function to provide logic with losing/adding health to the hit actor after overlapping
void AFPSAIProjProjectile::OnActorOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		//getting the health component to add logic, but GetComponentByClass returns objects of type UActorComponent, so it needs to be casted to a proper type
		UPHealthComponent* HealthComponent = Cast<UPHealthComponent>(OtherActor->GetComponentByClass(UPHealthComponent::StaticClass()));

		if(HealthComponent)
		{
			HealthComponent->ApplyHealthChange(GetInstigator(),-DamageAmount);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, OtherActor->GetActorLocation(), FRotator::ZeroRotator); //play sound at location of hit actor
			AudioComponent->Stop();
		}
	}
	Destroy();
}
