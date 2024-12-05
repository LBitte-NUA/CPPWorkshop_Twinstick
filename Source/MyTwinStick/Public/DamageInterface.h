// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Monster, // 0
	Player,  // 1
	Team_MAX UMETA(Hidden)
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYTWINSTICK_API IDamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ApplyDamage(AActor* Dealer, float Damage);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetHealth();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ETeam GetTeam();
};
