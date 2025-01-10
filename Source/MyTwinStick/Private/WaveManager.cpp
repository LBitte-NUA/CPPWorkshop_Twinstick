// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "WaveData.h"
#include "BaseCharacter.h"
#include "HealthComponent.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	// Check if WaveDataTable is set
	if (WaveDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave DT Read: Success"));
		StartWave();

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Wave DT Read: Failed"));
	}
	
}

void AWaveManager::StartWave()
{
	// Find and Set CurrentWave from the WaveDataTable using ('Wave_'CurrentWaveInt'') as the name
	if (CurrentWave = WaveDataTable->FindRow<FWaveData>(GetCurrentWaveName(), ""))
	{
		UE_LOG(LogTemp, Warning,TEXT("Wave | %i | Started"), CurrentWaveInt);
		// Reset SectionInt on a Start of a new wave
		SectionInt = 0;
		StartWaveSection();
	}
}

void AWaveManager::EndWave()
{
	float EndWaveInterval = CurrentWave->EndWaveInterval; // Save the value of Old WaveEndInterval
	UE_LOG(LogTemp, Warning, TEXT("Wave | %i | Ended"), CurrentWaveInt);

	CurrentWaveInt++; // Increment Current Wave Integer

	// Attempt to Find the new wave based on the incremented wave int
	if (CurrentWave = WaveDataTable->FindRow<FWaveData>(GetCurrentWaveName(), ""))
	{
		// Start the next wave after the EndWaveInterval of the old wave.
		GetWorldTimerManager().SetTimer(WaveHandle, this, &AWaveManager::StartWave, EndWaveInterval, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Wave | %i | NEXT WAVE NOT FOUND"), CurrentWaveInt);
	}
}

void AWaveManager::StartWaveSection()
{
	UE_LOG(LogTemp, Warning, TEXT("Section | %i | Started"), SectionInt);
	// Clear Enemies & bSpawningComplete on starting a new Wave Section
	EnemiesSpawned = 0;
	bSpawningComplete = false;
	// Start a Repeated Function to spawn enemies based on the Sections Spawn Interval
	GetWorldTimerManager().SetTimer(WaveHandle, this, &AWaveManager::SpawnEnemy, CurrentWave->Sections[SectionInt].SpawnInterval, true);
}

void AWaveManager::EndWaveSection()
{
	float EndSectionInterval = CurrentWave->Sections[SectionInt].EndSectionInterval; // Save the value of Old EndSectionInterval
	UE_LOG(LogTemp, Warning, TEXT("Section | %i | Ended"), SectionInt);

	// Increment Current Section Int
	SectionInt++;

	// Check if new section exists.
	if (CurrentWave->Sections.IsValidIndex(SectionInt))
	{	
		// Start next section after Old EndSectionInterval
		GetWorldTimerManager().SetTimer(WaveHandle, this, &AWaveManager::StartWaveSection, EndSectionInterval, false);
	}
	else
	{
		// New Section doesnt exists, All Sections Complete, Spawning finished.
		bSpawningComplete = true;
	}
}

void AWaveManager::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Generate Random Spawn Location Vector 
	FVector Location = FVector(FMath::FRandRange(-2000.f, 2000.f), // X
								FMath::FRandRange(-2000.f, 2000.f),// Y
										200.f);					   // Z
	FRotator Rotation = FRotator::ZeroRotator;

	// Spawn the Enemy
	ABaseCharacter* Enemy = GetWorld()->SpawnActor<ABaseCharacter>(CurrentWave->Sections[SectionInt].Enemy, Location, Rotation, SpawnParams);

	// Find if Enemy has Health Component
	if (UHealthComponent* EnemyHealth = Enemy->FindComponentByClass<UHealthComponent>())
	{
		// Bind to its Death and Increment How many enemies are currently alive.
		EnemyHealth->OnDeath.AddDynamic(this, &AWaveManager::OnEnemyDeath);
		EnemiesRemaining++;
	}

	EnemiesSpawned++; // Increase enemy spawn count

	// Check if Enemy Spawn count equals how many enemies to spawn
	if (EnemiesSpawned == CurrentWave->Sections[SectionInt].Amount)
	{
		// Stop Spawning and EndWaveSection
		GetWorldTimerManager().ClearTimer(WaveHandle);
		EndWaveSection();
	}
}

void AWaveManager::OnEnemyDeath(AActor* Enemy, AActor* Dealer)
{
	// Decrement Enemy count
	EnemiesRemaining--;

	// Find Enemy HealtHComponent
	if (UHealthComponent* EnemyHealth = Enemy->FindComponentByClass<UHealthComponent>())
	{
		// Remove OnDeath Binding from a Dead Enemy
		EnemyHealth->OnDeath.RemoveDynamic(this, &AWaveManager::OnEnemyDeath);
	}

	// Check if All Enemies are Spawned and Killed.
	if (bSpawningComplete && EnemiesRemaining == 0)
	{
		EndWave();
	}
}
