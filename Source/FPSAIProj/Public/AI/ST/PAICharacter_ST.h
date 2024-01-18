// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PAICharacter_ST.generated.h"

class UPHealthComponent;
class UAIPerceptionComponent;
class UStateTreeComponent;
UCLASS()
class FPSAIPROJ_API APAICharacter_ST : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APAICharacter_ST();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStateTreeComponent* StateTreeComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
