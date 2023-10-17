// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void APAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree); //running the behavior tree set in the editor

}
