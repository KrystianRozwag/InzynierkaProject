// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class UPActionComponent;
class AFPSAIProjCharacter;
UENUM(BlueprintType)
enum class E_FireMode : uint8
{
	SemiAuto    UMETA(DisplayName = "Semi-Automatic"),
	FullAuto    UMETA(DisplayName = "Full-Automatic"),
	Burst       UMETA(DisplayName = "Burst Fire")
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSAIPROJ_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AFPSAIProjProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPActionComponent* ActionComp;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SecondaryFireAction;
	// Header declarations
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	E_FireMode CurrentFireMode = E_FireMode::SemiAuto; // Default value


	UPROPERTY()
	FTimerHandle FullAutoTimerHandle;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFiring();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFiring();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AFPSAIProjCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	void SecondaryAttack();

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginPlay();
private:
	/** The Character holding this weapon*/
	AFPSAIProjCharacter* Character;
};
