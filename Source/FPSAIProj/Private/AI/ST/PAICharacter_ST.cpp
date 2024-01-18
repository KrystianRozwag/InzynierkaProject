// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ST/PAICharacter_ST.h"

#include "PHealthComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameplayStateTreeModule/Public/Components/StateTreeComponent.h"
// Sets default values
APAICharacter_ST::APAICharacter_ST()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	HealthComponent = CreateDefaultSubobject<UPHealthComponent>("HealthComponent");
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>("StateTreeComponent");
}

// Called when the game starts or when spawned
void APAICharacter_ST::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APAICharacter_ST::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APAICharacter_ST::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

