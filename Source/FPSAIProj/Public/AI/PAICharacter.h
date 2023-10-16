// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PAICharacter.generated.h"


class UPawnSensingComponent;

UCLASS()
class FPSAIPROJ_API APAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APAICharacter();

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

};
