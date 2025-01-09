// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine/DataTable.h"

#include "WaveData.generated.h"
/**
 * 
 */
class ABaseCharacter;

USTRUCT(BlueprintType)
struct FWaveSection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) // Enemy to Spawn
		TSubclassOf<ABaseCharacter> Enemy;

	UPROPERTY(EditAnywhere) // Amount of enemies to spawn
		int32 Amount = 0;

	UPROPERTY(EditAnywhere) // Time between enemy spawns
		float SpawnInterval = 0.1f;

	UPROPERTY(EditAnywhere) // Time before starting to spawn next section
		float EndSectionInterval = 0.5f;
};

USTRUCT(BlueprintType)
struct MYTWINSTICK_API FWaveData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FWaveSection> Sections;

	UPROPERTY(EditAnywhere)
	float EndWaveInterval = 0.f;
};

