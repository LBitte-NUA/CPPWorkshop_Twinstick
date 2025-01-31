// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "WaveData.h"
#include "BaseCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnPoint.h"

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

	// Register Spawnpoints
	InitializeSpawnPoints();

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
	// Set Default Values
	FVector Location = FVector(0.f, 0.f, 500.f); // Default Spawn Location if SpawnPoints don't exist.
	FRotator Rotation = FRotator::ZeroRotator;

	// Check if we've successfuly found a Random SpawnPoint
	if (ASpawnPoint* SPoint = GetRandomSPoint())
	{
		// Replace Values with the SpawnPoint ones.
		Location = SPoint->GetActorLocation();
		Rotation = SPoint->GetActorRotation();
	}

	// Spawn the Enemy
	ABaseCharacter* Enemy = GetWorld()->SpawnActor<ABaseCharacter>(CurrentWave->Sections[SectionInt].Enemy, Location, Rotation, SpawnParams);

	if (IsValid(Enemy))
	{
		// Find if Enemy has Health Component
		if (UHealthComponent* EnemyHealth = Enemy->FindComponentByClass<UHealthComponent>())
		{
			// Bind to its Death and Increment How many enemies are currently alive.
			EnemyHealth->OnDeath.AddDynamic(this, &AWaveManager::OnEnemyDeath);
			EnemiesRemaining++;
		}
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

void AWaveManager::InitializeSpawnPoints()
{
	TArray<AActor*> SpawnPoints; // Containter for GetAllActorOfClass()

	// NOTE1: To use UGameplayStatics we must #include "Kismet/GameplayStatics.h"
	// NOTE2: Be sure to #include "SpawnPoint.h" 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), SpawnPoints);
	                                 /*  (World Context,   Class to Find,  Container to Store);  */

	for (auto Point : SpawnPoints) // We Iterate through all of the Spawnpoints
	{
		if (ASpawnPoint* SPoint = Cast<ASpawnPoint>(Point)) // Recognise the Actor as a Spawnpoint
		{
			if (SPoint->GetCurrentStatus()) // Check Default Status
			{
				ActiveSpawnPoints.Add(SPoint); // Add to Active Spawn points if Active
			}
			// Bind to All Spawnpoints
			SPoint->OnStatusUpdated.BindDynamic(this, &AWaveManager::OnPointStatusChanged);
		}
	}
}

// Bound to SpawnPoints Update Delegate (Hence the Same Parameters)
void AWaveManager::OnPointStatusChanged(bool NewStatus, ASpawnPoint* SpawnPoint)
{
	if (NewStatus)
		ActiveSpawnPoints.AddUnique(SpawnPoint);// Status True = Add to Active
	else
		ActiveSpawnPoints.Remove(SpawnPoint);	// Status False = Remove from Active
}

// Return a Random SpawnPoint from the Array.
ASpawnPoint* AWaveManager::GetRandomSPoint()
{
	// Get a Random Integer from 0 to ElementsInArray - 1 
	// -1 as we are looking for index
	int32 randomInt = FMath::RandRange(0, ActiveSpawnPoints.Num()-1);
	// Check if the Return is valid
	if (ActiveSpawnPoints.IsValidIndex(randomInt))
	{
		return ActiveSpawnPoints[randomInt];
	}
	return nullptr;
}
