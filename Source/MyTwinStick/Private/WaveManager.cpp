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
	if (CurrentWave = WaveDataTable->FindRow<FWaveData>(GetCurrentWaveName(), ""))
	{
		UE_LOG(LogTemp, Warning,TEXT("Wave | %i | Started"), CurrentWaveInt);
		SectionInt = 0;
		StartWaveSection();
	}
}

void AWaveManager::EndWave()
{
	UE_LOG(LogTemp, Warning, TEXT("Wave | %i | Ended"), CurrentWaveInt);
	
	if (CurrentWave = WaveDataTable->FindRow<FWaveData>(GetCurrentWaveName(), ""))
	{
		GetWorldTimerManager().SetTimer(WaveHandle, this, &AWaveManager::StartWave, CurrentWave->EndWaveInterval, false);
		CurrentWaveInt++;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Wave | %i | NEXT WAVE NOT FOUND"), CurrentWaveInt);
	}
}

void AWaveManager::StartWaveSection()
{
	UE_LOG(LogTemp, Warning, TEXT("Section | %i | Started"), SectionInt);
	EnemiesSpawned = 0;
	bSpawningComplete = false;
	GetWorldTimerManager().SetTimer(WaveHandle, this, &AWaveManager::SpawnEnemy, CurrentWave->Sections[SectionInt].SpawnInterval, true);
}

void AWaveManager::EndWaveSection()
{
	UE_LOG(LogTemp, Warning, TEXT("Section | %i | Ended"), SectionInt);
	SectionInt++;
	if (CurrentWave->Sections.IsValidIndex(SectionInt))
	{
		GetWorldTimerManager().SetTimer(WaveHandle, this, &AWaveManager::StartWaveSection, CurrentWave->Sections[SectionInt].EndSectionInterval, false);
	}
	else
	{
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

	ABaseCharacter* Enemy = GetWorld()->SpawnActor<ABaseCharacter>(CurrentWave->Sections[SectionInt].Enemy, Location, Rotation, SpawnParams);
	if (UHealthComponent* EnemyHealth = Enemy->FindComponentByClass<UHealthComponent>())
	{
		EnemyHealth->OnDeath.AddDynamic(this, &AWaveManager::OnEnemyDeath);
		EnemiesRemaining++;
	}

	EnemiesSpawned++;

	if (EnemiesSpawned == CurrentWave->Sections[SectionInt].Amount)
	{
		GetWorldTimerManager().ClearTimer(WaveHandle);
		EndWaveSection();
	}
}

void AWaveManager::OnEnemyDeath()
{
	EnemiesRemaining--;

	if (bSpawningComplete && EnemiesRemaining == 0)
	{
		EndWave();
	}
}
