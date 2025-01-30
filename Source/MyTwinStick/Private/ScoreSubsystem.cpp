// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSubsystem.h"
#include "WeaponUnlockSubsystem.h"

void UScoreSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Score Initialised"));
}

void UScoreSubsystem::Deinitialize()
{
}

void UScoreSubsystem::IncreaseScore(int32 Value)
{
	Score += Value;
	OnScoreUpdated.Broadcast(Score);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Score Increased"));
	UWeaponUnlockSubsystem* UnlockSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWeaponUnlockSubsystem>();
	UnlockSubsystem->IncreaseCondition(EUnlockCondition::PlayerScore, Value);
}

void UScoreSubsystem::DecreaseScore(int32 Value)
{
	Score -= Value;
	OnScoreUpdated.Broadcast(Score);
}
