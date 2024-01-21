// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PAICharacterBase.generated.h"
class UPHealthComponent;
UCLASS()
class FPSAIPROJ_API APAICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APAICharacterBase();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeOfHitParamName;

	void SetTarget(AActor* NewTarget);

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPHealthComponent* HealthComponent;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth, float Delta);
};
