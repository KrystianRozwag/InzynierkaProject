// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PAICharacter.generated.h"


class UPawnSensingComponent;
class UPHealthComponent;
UCLASS()
class FPSAIPROJ_API APAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APAICharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName TimeOfHitParamName;

	void SetTarget(AActor* NewTarget);

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth, float Delta);
};
