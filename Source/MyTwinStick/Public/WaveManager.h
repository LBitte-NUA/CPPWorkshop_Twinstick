// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

struct FWaveData;
class ASpawnPoint;

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

	void StartWave();		// Called to Start Wave
	void EndWave();			// Called at End of Wave
	void StartWaveSection();// Called to Start Wave Section
	void EndWaveSection();	// Called at End of Wave Section
	void SpawnEnemy();		// Spawn an Enemy

	UFUNCTION()
	void OnEnemyDeath(AActor* Enemy, AActor* Dealer);	// Bound to a Spawned Enemies Death.

	// The Data table used to spawn enemies.
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "True"))
	class UDataTable* WaveDataTable;

	int32 CurrentWaveInt = 1;	// Keep track of current Wave
	int32 SectionInt = 0;		// Keep track of current Wave Section
	int32 EnemiesSpawned = 0;	// How many enemies have been spawned (To stop a wave Section)
	int32 EnemiesRemaining = 0; // How many enemies currently are alive (To end a wave)

	bool bSpawningComplete = false; // Have all Wave Sections finished spawning

	const FWaveData* CurrentWave;	// Reference to Data Table Row (WaveData)

	FTimerHandle WaveHandle;		// Timer used for Latent Functionality (Spawning/EndWaveSection/EndWave)

	const FString RowName = TEXT("Wave_");	// Base Row Name

	// Append 'Wave_' + 'CurrentWaveInt' 
	// Example:
	// CurrentWaveInt = 3 
	// Returns 'Wave_3'
	FORCEINLINE FName GetCurrentWaveName() { return FName(*(RowName + FString::FromInt(CurrentWaveInt))); }

	/********** Spawn Points ***********/
	UPROPERTY()
	TArray<ASpawnPoint*> ActiveSpawnPoints;
	void InitializeSpawnPoints();

	UFUNCTION()
	void OnPointStatusChanged(bool NewStatus, ASpawnPoint* SpawnPoint);

	ASpawnPoint* GetRandomSPoint();

};
