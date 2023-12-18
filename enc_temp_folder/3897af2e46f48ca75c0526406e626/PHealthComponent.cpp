// Fill out your copyright notice in the Description page of Project Settings.


#include "PHealthComponent.h"

// Sets default values for this component's properties
UPHealthComponent::UPHealthComponent()
{
	HealthMax = 100;
	Health = HealthMax;
}

bool UPHealthComponent::IsPawnAlive()
{
	if(Health > 0.0f)
	{
		return true;
	}
	return false;
}

float UPHealthComponent::GetHealthMax() const
{
	return HealthMax;
}
float UPHealthComponent::GetHealth() const
{
	return Health;
}
bool UPHealthComponent::ApplyHealthChange(AActor* Actor, float Delta)
{
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);

	//float NewDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(Actor, this, Health, Delta);
	return Delta < 0;
}
