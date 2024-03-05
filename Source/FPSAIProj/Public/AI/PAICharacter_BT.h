// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/PAICharacterBase.h"
#include "PAICharacter_BT.generated.h"

class UPawnSensingComponent;
class UPHealthComponent;
UCLASS()
class FPSAIPROJ_API APAICharacter_BT : public APAICharacterBase
{
	GENERATED_BODY()
public:
	APAICharacter_BT();
protected:

//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
//	UPHealthComponent* HealthComponent;

//	UPROPERTY(VisibleAnywhere, Category = "Effects")
//	FName TimeOfHitParamName;

	void SetTarget(AActor* NewTarget);

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth, float Delta) override;
};
