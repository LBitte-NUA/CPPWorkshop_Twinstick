// Fill out your copyright notice in the Description page of Project Settings.


#include "AIManager.h"
#include "SmartAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAIManager::AAIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIManager::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(UpdateHandle, this, &AAIManager::UpdateEnemyAI, 0.5f, true);
}

// Called every frame
void AAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSet<APawn*> AAIManager::GetClosestEnemiesToTarget(AActor* Target, int8 val)
{
	TSet<APawn*> CloseEnemies;

	for (auto Enemy : AllEnemies)
	{
		/* Add First 'x' Amount of Enemies to 'close'*/
		if (CloseEnemies.Num() < AmountSmartControllers)
		{
			CloseEnemies.Add(Enemy);
			continue;
		}

		// Compare each enemy againts close enemies.
		for (auto CloseEnemy : CloseEnemies)
		{
			if (IsACloserThanBToTarget(Enemy, CloseEnemy, Target))
			{
				CloseEnemies.Remove(CloseEnemy);
				CloseEnemies.Add(Enemy);
				break;
			}
		}
	}
	return CloseEnemies;
}

bool AAIManager::IsACloserThanBToTarget(APawn* EnemyA, APawn* EnemyB, AActor* Target)
{
	double DistA, DistB;
	DistA = FVector::Distance(EnemyA->GetActorLocation(), Target->GetActorLocation());
	DistB = FVector::Distance(EnemyB->GetActorLocation(), Target->GetActorLocation());

	return DistA < DistB;
}

void AAIManager::UpdateEnemyAI()
{
	TArray<AActor*> AllEnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, AllEnemyActors);
	
	// DEAD ENEMIES REMAIN IN THE ALLENEMIES ARRAY!!!!
	// 
	// TODO: Link with WaveManager and EnemyHealth Comp 
	// to add and remove enemies from array dynamically.

	for (auto Enemy : AllEnemyActors)
	{
		APawn* EnemyPawn = Cast<APawn>(Enemy);
		AllEnemies.AddUnique(EnemyPawn);

		// If enemy is within 'closest Enemies'
		if (GetClosestEnemiesToTarget(GetWorld()->GetFirstPlayerController()->GetPawn()).Contains(EnemyPawn))
		{
			if (!Cast<ASmartAIController>(EnemyPawn->GetController()))
			{
				ASmartAIController* SmartCont = GetWorld()->SpawnActor<ASmartAIController>(SmartController);
				SmartCont->Possess(EnemyPawn);
			}
			continue;
		}

		if (Cast<ASmartAIController>(EnemyPawn->GetController()))
		{
			AController* DumbCont = GetWorld()->SpawnActor<AController>(DumbController);
			DumbCont->Possess(EnemyPawn);
		}
	}
}


