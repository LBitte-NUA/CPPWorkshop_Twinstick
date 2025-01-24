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

private:
	// T* and TObjectPtr<T> Are Practically the same in packaged builds
	// However, Unreal wants you to use TObjectPtr<T> When declaring members in your .h files.
	// NOTE: Unnecessery to use in local function or returns.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UBoxComponent> BoxCollider; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "True"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/* To Be Continued AInteractableActor.H */

public:
	// Override the Interface OnInteract() Function
	virtual void OnInteract(APlayerController* Player) override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "True"))
	int32 ScoreRequirement; // Score requirement to interact

	void Interacted();
	bool isOpen = false; // Make sure we can only open the door once

public:
	// Linked Spawn points that we wish to 'Active'
	UPROPERTY(EditAnywhere)
	TArray<ASpawnPoint*> SpawnPoints;

protected:
	// Used in Blueprints to Update Visuals
	UFUNCTION(BlueprintImplementableEvent)
	void Interacted_BP();
};
