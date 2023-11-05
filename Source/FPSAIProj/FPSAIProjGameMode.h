// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "FPSAIProjGameMode.generated.h"
class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
UCLASS(minimalapi)
class AFPSAIProjGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnEnemyQuery;

	FTimerHandle TimerHandle_SpawnEnemies;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;
	UFUNCTION()
	void SpawnEnemyTimerElapsed();
	UFUNCTION()
	void OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
public:
	AFPSAIProjGameMode();


	virtual void StartPlay() override;
};



