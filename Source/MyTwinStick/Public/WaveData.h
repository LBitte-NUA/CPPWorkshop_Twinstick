// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveData.generated.h"
/**
 * 
 */
class ABaseCharacter;

USTRUCT(BlueprintType)
struct FWaveSection
{
	/* 
	*  FWaveSection Struct contains the data of
	*  each individual wave section, which there
	*  can be multiple of in each wave. 
	*/

	GENERATED_BODY()

	// Enemy to Spawn
	UPROPERTY(EditAnywhere) 
		TSubclassOf<ABaseCharacter> Enemy;

	// Amount of enemies to spawn
	UPROPERTY(EditAnywhere) 
		int32 Amount = 0;

	// Time between enemy spawns
	UPROPERTY(EditAnywhere) 
		float SpawnInterval = 0.1f;

	// Time before starting to spawn next section
	UPROPERTY(EditAnywhere) 
		float EndSectionInterval = 0.5f;
};

USTRUCT(BlueprintType)
struct MYTWINSTICK_API FWaveData : public FTableRowBase
{
	/*
	* FWaveData struct is used to populate a WaveSpawning Data table
	* to be used by WaveManager Class to spawn enemies.
	*/

	GENERATED_BODY()

	// Array of wave sections to spawn every wave.
	UPROPERTY(EditAnywhere, meta=(ShowOnlyInnerProperties))
	TArray<FWaveSection> Sections;

	// Time at the end of the wave before next wave starts.
	UPROPERTY(EditAnywhere)
	float EndWaveInterval = 0.f;
};

