// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnPoint.generated.h"

// Delegate called when the Spawnpoints Status has been updated.
DECLARE_DYNAMIC_DELEGATE_TwoParams(
		FOnSpawnPointStatusUpdatedSignature,// Signature
		bool, NewStatus,					// bCurrentStatus 	
		ASpawnPoint*, SpawnPoint);			// This Spawnpoint

UCLASS()
class MYTWINSTICK_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FOnSpawnPointStatusUpdatedSignature OnStatusUpdated;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "True"))
	bool bCurrentStatus; // Should the Spawnpoint be used? (Yes/No)

public: // Getter & Setter
	FORCEINLINE bool GetCurrentStatus() { return bCurrentStatus; }
	void SetCurrentStatus(bool newStatus);
};


