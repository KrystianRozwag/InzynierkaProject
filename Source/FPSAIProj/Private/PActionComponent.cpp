// Fill out your copyright notice in the Description page of Project Settings.


#include "PActionComponent.h"

#include "PAction.h"


UPActionComponent::UPActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}



void UPActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UPActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UPActionComponent::AddAction(TSubclassOf<UPAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}


	UPAction* NewAction = NewObject<UPAction>(this, ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UPActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(UPAction* Action : Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UPActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UPAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}

