// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "InteractableActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ASpawnPoint;

UCLASS()
class MYTWINSTICK_API AInteractableActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnInteract(APlayerController* Player) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	int32 ScoreRequirement;

private:
	void Interacted();
	bool isOpen = false;

public:
	UPROPERTY(EditAnywhere)
	TArray<ASpawnPoint*> SpawnPoints;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Interacted_BP();
};
