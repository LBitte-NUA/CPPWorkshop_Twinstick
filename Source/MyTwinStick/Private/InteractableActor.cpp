// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ScoreSubsystem.h"
#include "SpawnPoint.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;
	BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(BoxCollider);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableActor::OnInteract(APlayerController* Player)
{
	//UE_LOG(LogTemp, Warning, TEXT("INTERACTED"));
	if (Player == nullptr) { return; }
	
	UScoreSubsystem* PlayerScore = ULocalPlayer::GetSubsystem<UScoreSubsystem>(Player->GetLocalPlayer());
	if (ScoreRequirement <= PlayerScore->Score)
	{
		Interacted();
		PlayerScore->DecreaseScore(ScoreRequirement);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Score Required: %i"), ScoreRequirement));
		//UE_LOG(LogTemp, Warning, TEXT("Score Required: %i"), ScoreRequirement);
	}
}

void AInteractableActor::Interacted()
{
	for (ASpawnPoint* point : SpawnPoints)
	{
		if(point != nullptr)
			point->SetCurrentStatus(true);
	}
	Destroy();
}


