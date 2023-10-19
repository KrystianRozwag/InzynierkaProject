// Fill out your copyright notice in the Description page of Project Settings.


#include "PHealthComponent.h"

// Sets default values for this component's properties
UPHealthComponent::UPHealthComponent()
{
	Health = 100;
}

bool UPHealthComponent::IsPawnAlive()
{
	return true ? Health > 0.f : false;
}


bool UPHealthComponent::ApplyHealthChange(float Delta)
{

	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}
