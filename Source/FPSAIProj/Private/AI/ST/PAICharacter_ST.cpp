// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ST/PAICharacter_ST.h"


#include "Perception/AIPerceptionComponent.h"
#include "GameplayStateTreeModule/Public/Components/StateTreeComponent.h"
// Sets default values
APAICharacter_ST::APAICharacter_ST()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>("StateTreeComponent");
}
