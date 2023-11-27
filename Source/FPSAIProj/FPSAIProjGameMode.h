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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float RespawnDelay;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	int CreditsForKill;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> EnemyClass;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

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

	UFUNCTION()
	void RespawnPlayerTimeElapsed(AController* Controller);

	UFUNCTION()
	int CountEnemiesWithHealthComponent() const;

	UFUNCTION()
	float GetMaxNumOfEnemies() const;
public:
	AFPSAIProjGameMode();

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	virtual void StartPlay() override;


	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
};



