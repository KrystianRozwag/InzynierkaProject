// Fill out your copyright notice in the Description page of Project Settings.


#include "CreditsPlayerState.h"

int ACreditsPlayerState::GetPoints() const
{
	return Points;
}

void ACreditsPlayerState::ApplyPointsChange(int Delta)
{
	if(Delta>0.0f)
	{
		Points += Delta;
		OnPointsChanged.Broadcast(this, Points, Delta);
	}
}
