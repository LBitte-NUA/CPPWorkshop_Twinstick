// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponStats.generated.h"
/**
 * 
 */
UENUM()
enum class EW_FireType : uint8
{
	// continuous Weapon Fire while fire is held
	Automatic UMETA(DisplayName = "Automatic"),
	// Every shot needs to be pressed individually.
	Semi      UMETA(DisplayName = "Semi-Automatic"),
	FireType_MAX UMETA(Hidden)
};

UENUM()
enum class EW_ReloadType : uint8
{
	// Reload the entire clip
	Full,
	// Reload single shot.
	Single,
	ReloadType_MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct MYTWINSTICK_API FWeaponStats
{
	GENERATED_BODY();
	// Minimum Weapon Damage Roll
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Damage", meta = (ClampMin = "1"))
	int32 MinDamage = 1;
	// Maximum Weapon Damage Roll
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "1"))
	int32 MaxDamage = 5;


	// Time Between shots (in Seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Rate", meta = (ClampMin = "0.01"))
	float FireInterval = 0.5f;
	// Weapon Fire Trigger Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Rate")
	EW_FireType FireType = EW_FireType::Automatic;

	// Bullets Fired per shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Shot", meta = (ClampMin = "1", ClampMax = "20"))
	int32 BulletsPerShot = 1;
	// Accuracy variance per bullet (Lower = Better)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shot", meta = (ClampMin = "0"))
	float BulletAimOffset = 0;


	// Time to Reload (in Seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reload", meta = (ClampMin = "0.01"))
	float ReloadInterval = 1.2f;
	// Reload Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reload")
	EW_ReloadType ReloadType = EW_ReloadType::Full;
	// Maximum Clip Size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reload", meta = (ClampMin = "1"))
	int32 ClipSize = 8;

};

USTRUCT(BlueprintType)
struct MYTWINSTICK_API FItemData
{
	GENERATED_BODY();
	// Text used for Name of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	// Text used for description of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

};
