// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnPoint.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSpawnPointStatusUpdatedSignature, bool, NewStatus, ASpawnPoint*, SpawnPoint);

UCLASS()
class MYTWINSTICK_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FOnSpawnPointStatusUpdatedSignature OnStatusUpdated;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "True"))
	bool bCurrentStatus;

public:
	bool GetCurrentStatus() { return bCurrentStatus; }
	void SetCurrentStatus(bool newStatus);

};
