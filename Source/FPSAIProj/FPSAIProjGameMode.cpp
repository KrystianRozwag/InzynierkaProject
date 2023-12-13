// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSAIProjGameMode.h"

#include "CreditsPlayerState.h"
#include "EngineUtils.h"
#include "FPSAIProjCharacter.h"
#include "PHealthComponent.h"
#include "TimerManager.h"
#include "AI/PAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSAIProjGameMode::AFPSAIProjGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	SpawnTimerInterval = 2.f;

	RespawnDelay = 5.f;

	CreditsForKill = 10;
	PlayerStateClass = ACreditsPlayerState::StaticClass();
}


void AFPSAIProjGameMode::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnEnemies, this, &AFPSAIProjGameMode::SpawnEnemyTimerElapsed, SpawnTimerInterval, true);
}

void AFPSAIProjGameMode::SpawnEnemyTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnEnemyQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if(QueryInstance)
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AFPSAIProjGameMode::OnQueryFinished);
	}
}

int AFPSAIProjGameMode::CountEnemiesWithHealthComponent() const
{
	int NumOfEnemies = 0;

	for (TActorIterator<APAICharacter> It(GetWorld()); It; ++It)
	{
		APAICharacter* Enemy = *It;
		UPHealthComponent* HealthComponent = Enemy->FindComponentByClass<UPHealthComponent>();

		if (HealthComponent)
		{
			NumOfEnemies++;
		}
	}

	return NumOfEnemies;
}

float AFPSAIProjGameMode::GetMaxNumOfEnemies() const
{
	float MaxNumOfEnemies = 10.f;

	if (DifficultyCurve)
	{
		MaxNumOfEnemies = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	return MaxNumOfEnemies;
}

void AFPSAIProjGameMode::OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{

	if(QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}

	int NumOfEnemies = CountEnemiesWithHealthComponent();
	float MaxNumOfEnemies = GetMaxNumOfEnemies();


	if(NumOfEnemies >= MaxNumOfEnemies)
	{
		return;
	}

	TArray<FVector> LocationsToSpawnEnemies;
	QueryInstance->GetQueryResultsAsLocations(LocationsToSpawnEnemies);

	if(LocationsToSpawnEnemies.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(EnemyClass, LocationsToSpawnEnemies[0], FRotator::ZeroRotator);
	}
}

void AFPSAIProjGameMode::RespawnPlayerTimeElapsed(AController* Controller)
{
	if(!Controller)
	{
		return;
	}
	APlayerController* Player = Cast<APlayerController>(Controller);
	if (Player)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "AIProjMap");
	}
}

void AFPSAIProjGameMode::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	AFPSAIProjCharacter* Player = Cast<AFPSAIProjCharacter>(VictimActor);
	APAICharacter* AICharacter = Cast<APAICharacter>(Killer);
	if (Player) //if player killed
	{
		FTimerHandle TimerHandle_PlayerRespawnDelay;

		FTimerDelegate RespawnDelegate;
		RespawnDelegate.BindUFunction(this, "RespawnPlayerTimeElapsed", Player->GetController()); //bind RespawnPlayerTimeElapsed function, so after delay it will run and restart the game

		GetWorldTimerManager().SetTimer(TimerHandle_PlayerRespawnDelay, RespawnDelegate, RespawnDelay, false);
		AICharacter->GetCharacterMovement()->DisableMovement();
		Player->GetCharacterMovement()->StopMovementImmediately();
	}

	APawn* KillerPawn = Cast<APawn>(Killer);
	ACreditsPlayerState* PlayerState = KillerPawn->GetPlayerState<ACreditsPlayerState>();

	if (PlayerState && KillerPawn)
	{
		PlayerState->ApplyPointsChange(CreditsForKill);
	}
}
