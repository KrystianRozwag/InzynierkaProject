// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSAIProjGameMode.h"

#include "CreditsPlayerState.h"
#include "EngineUtils.h"
#include "FPSAIProjCharacter.h"
#include "PHealthComponent.h"
#include "AI/PAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSAIProjGameMode::AFPSAIProjGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	SpawnTimerInterval = 2.f;

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

void AFPSAIProjGameMode::OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{

	if(QueryStatus != EEnvQueryStatus::Success)
	{
			return;
	}


	int NumOfEnemies = 0;
	for (TActorIterator<APAICharacter> It(GetWorld()); It; ++It) //using template for actor iteration. GetWorld() is passed to get all actors of class PAICharacter in the world
	{
		APAICharacter* Enemy = *It;
		UPHealthComponent* HealthComponent = Cast<UPHealthComponent>(Enemy->GetComponentByClass(UPHealthComponent::StaticClass()));
		if(HealthComponent)
		{
			NumOfEnemies++;
		}
	}

	float MaxNumOfEnemies = 10.f;

	if (DifficultyCurve)
	{
		MaxNumOfEnemies = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	if(NumOfEnemies >= MaxNumOfEnemies)
	{
		return;
	}

	TArray<FVector> LocationsToSpawn;
	QueryInstance->GetQueryResultsAsLocations(LocationsToSpawn);
	if(LocationsToSpawn.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(EnemyClass, LocationsToSpawn[0], FRotator::ZeroRotator);

	}

}

void AFPSAIProjGameMode::RespawnPlayerElapsed(AController* Controller)
{
	if (Controller)
	{
		//Controller->UnPossess();
		//RestartPlayer(Controller);
		APlayerController* Player = Cast<APlayerController>(Controller);
		if (Player)
		{
			//Player->bEnableClickEvents = 1; //temp fix
			//Player->GetCharacter()->GetCapsuleComponent()->SetCollisionProfileName("CharacterMesh");
			//Controller->Possess(Player->GetPawn());
			UGameplayStatics::OpenLevel(GetWorld(), "AIProjMap");
		}

	}
}
void AFPSAIProjGameMode::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	AFPSAIProjCharacter* Player = Cast<AFPSAIProjCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}

	APawn* KillerPawn = Cast<APawn>(Killer);
	if (KillerPawn)
	{
		ACreditsPlayerState* PlayerState = KillerPawn->GetPlayerState<ACreditsPlayerState>();
		if (PlayerState)
		{
			PlayerState->ApplyCreditsChange(CreditsForKill);
		}
	}
}
