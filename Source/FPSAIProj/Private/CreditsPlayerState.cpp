// Fill out your copyright notice in the Description page of Project Settings.


#include "CreditsPlayerState.h"

int ACreditsPlayerState::GetCredits() const
{
	return Credits;
}

void ACreditsPlayerState::ApplyCreditsChange(int Delta)
{
	if(Delta>0.0f)
	{
		Credits += Delta;
		OnCreditsChanged.Broadcast(this, Credits, Delta);
	}
}
