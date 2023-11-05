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
	return true ? Health > 0.f : false;
}

float UPHealthComponent::GetHealthMax() const
{
	return HealthMax;
}
float UPHealthComponent::GetHealth() const
{
	return Health;
}
bool UPHealthComponent::ApplyHealthChange(AActor* ActorPlayer, float Delta)
{
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);

	float NewDelta = Health - OldHealth;

	Health += Delta;
	OnHealthChanged.Broadcast(ActorPlayer, this, Health, NewDelta);
	return NewDelta != 0;
}
