// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/PAICharacterBase.h"
#include "PAICharacter_ST.generated.h"


class UAIPerceptionComponent;
class UStateTreeComponent;
UCLASS()
class FPSAIPROJ_API APAICharacter_ST : public APAICharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APAICharacter_ST();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAIPerceptionComponent* PerceptionComponent;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStateTreeComponent* StateTreeComponent;


	UFUNCTION()
	virtual void OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth, float Delta) override;
};
