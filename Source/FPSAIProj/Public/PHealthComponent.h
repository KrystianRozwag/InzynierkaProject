// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, Instigator, UPHealthComponent*, OwningComp, float, NewHealth, float, Delta);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSAIPROJ_API UPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPHealthComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float Health;

public:
	UFUNCTION(BlueprintCallable)
	bool IsPawnAlive();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category="Health")
	bool ApplyHealthChange(float Delta);
};
