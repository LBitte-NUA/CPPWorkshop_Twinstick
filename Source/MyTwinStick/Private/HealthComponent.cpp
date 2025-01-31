// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ScoreSubsystem.h"

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

#if WITH_EDITOR
void UHealthComponent::PostEditChangeProperty(FPropertyChangedEvent& ChangedProperty)
{
	Super::PostEditChangeProperty(ChangedProperty);

	ResetHealth();
}
#endif

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
	OnHealthModified.Broadcast(Health);
}

void UHealthComponent::DecreaseHealth_Internal(AActor* Dealer, float value)
{
	if ((Health - value) < 0.f)
	{
		Health = 0;
		Death(Dealer);
	}
	else
	{
		Health -= value; // Health = Health - Value
	}
	OnHealthModified.Broadcast(Health);
}

void UHealthComponent::Death(AActor* Dealer)
{
	UE_LOG(LogTemp, Warning, TEXT("%s - Has Died"), *GetOwner()->GetActorNameOrLabel());
	OnDeath.Broadcast(GetOwner(), Dealer);
}

void UHealthComponent::ApplyDamage_Implementation(AActor* Dealer, float Damage)
{
	if (GetOwner() == Dealer) { return; } // Don't do Damage to SELF!

	DecreaseHealth_Internal(Dealer,Damage);
	/*
	if (APawn* Player = Cast<APawn>(Dealer))
	{
		if (APlayerController* PCont = Cast<APlayerController>(Player->GetController()))
		{
			if (UScoreSubsystem* PlayerScore = ULocalPlayer::GetSubsystem<UScoreSubsystem>(PCont->GetLocalPlayer()))
			{
				// Add score to player when they do damage.
				PlayerScore->IncreaseScore(5);
			}
		}
	}
	*/

}

// TODO: Finish Health REGEN!!
void UHealthComponent::StartRegen()
{
	GetWorld()->GetTimerManager().SetTimer(RegenHandle, FTimerDelegate::CreateLambda([&] {IncreaseHealth_Internal(HealthRegen);}), 1.0f, false);
}

void UHealthComponent::StopRegen()
{
	GetWorld()->GetTimerManager().PauseTimer(RegenHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenResetHandle, FTimerDelegate::CreateLambda([&] {GetWorld()->GetTimerManager().UnPauseTimer(RegenHandle);}), RegenResetTime, false);
}

