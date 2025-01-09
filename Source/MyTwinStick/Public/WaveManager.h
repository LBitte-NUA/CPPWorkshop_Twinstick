// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

struct FWaveData;

UCLASS()
class MYTWINSTICK_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void StartWave();
	void EndWave();
	void StartWaveSection();
	void EndWaveSection();
	void SpawnEnemy();

	UFUNCTION()
	void OnEnemyDeath();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "True"))
	class UDataTable* WaveDataTable;

	int32 CurrentWaveInt = 1;
	int32 SectionInt = 0;
	int32 EnemiesSpawned = 0;
	int32 EnemiesRemaining = 0;

	bool bSpawningComplete = false;

	const FWaveData* CurrentWave;

	FTimerHandle WaveHandle;

	const FString RowName = TEXT("Wave_");

	FORCEINLINE FName GetCurrentWaveName() { return FName(*(RowName + FString::FromInt(CurrentWaveInt))); }

};
