// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::PostEditChangeProperty(FPropertyChangedEvent& ChangedProperty)
{
	Super::PostEditChangeProperty(ChangedProperty);

	ResetHealth();
}

void UHealthComponent::IncreaseHealth_Internal(float value)
{
	if ((Health + value) > MaxHealth)
	{
		Health = MaxHealth;
	}
	else
	{
		Health += value; // Health = Health + Value
	}
}

void UHealthComponent::DecreaseHealth_Internal(float value)
{
	if ((Health - value) < 0.f)
	{
		Health = 0;
		Death();
	}
	else
	{
		Health -= value; // Health = Health - Value
	}
	OnHealthModified.Broadcast(Health);
}

void UHealthComponent::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("DEATH"));
	GetOwner()->Destroy();
}

void UHealthComponent::ApplyDamage_Implementation(AActor* Dealer, float Damage)
{
	DecreaseHealth_Internal(Damage);
}

