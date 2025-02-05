// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManager.generated.h"

class ASmartAIController;

UCLASS()
class MYTWINSTICK_API AAIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "True"))
	TSubclassOf<APawn> EnemyClass;

	UPROPERTY()
	TArray<APawn*> AllEnemies;

	TSet<APawn*> GetClosestEnemiesToTarget(AActor* Target, int8 val = 10);

	TArray<ASmartAIController*> SmartAICollection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "True"))
	TSubclassOf<ASmartAIController> SmartController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "True"))
	TSubclassOf<AController> DumbController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "True"))
	int32 AmountSmartControllers = 10;

	
	bool IsACloserThanBToTarget(APawn* EnemyA, APawn* EnemyB, AActor* Target);
	
	void UpdateEnemyAI();

	FTimerHandle UpdateHandle;

};


