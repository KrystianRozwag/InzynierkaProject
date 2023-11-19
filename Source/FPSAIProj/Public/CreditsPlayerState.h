// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CreditsPlayerState.generated.h"

//declaring on event change to observe for credits change based on event rather than every tick so its better optimized
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ACreditsPlayerState*, PlayerState, int, NewCredits, int, Delta); 

UCLASS()
class FPSAIPROJ_API ACreditsPlayerState : public APlayerState
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, Category="Credits")
	int Credits;

public:
	UFUNCTION(BlueprintCallable, Category="Credits")
	int GetCredits() const;

	UFUNCTION(BlueprintCallable, Category="Credits")
	void ApplyCreditsChange(int Delta);

	UPROPERTY(BlueprintAssignable, Category="Credits")
	FOnCreditsChanged OnCreditsChanged;
};
