// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SmartAIController.generated.h"

/**
 * 
 */

UCLASS()
class MYTWINSTICK_API ASmartAIController : public AAIController
{
	GENERATED_BODY()
	

private:
	bool bIsActive = false;

public:
	FORCEINLINE bool GetActiveStatus() { return bIsActive; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActiveStatus(bool status) { bIsActive = status; }
	
};
