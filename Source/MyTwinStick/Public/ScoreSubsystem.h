// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScoreSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdatedSignature, int32, newScore);

UCLASS()
class MYTWINSTICK_API UScoreSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Score;

	UFUNCTION(BlueprintCallable)
	void IncreaseScore(int32 Value);

	UFUNCTION(BlueprintCallable)
	void DecreaseScore(int32 Value);

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdatedSignature OnScoreUpdated;
};
