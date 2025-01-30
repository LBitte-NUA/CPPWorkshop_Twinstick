// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeaponUnlockSubsystem.generated.h"

class UWeaponDataAsset;

UENUM(BlueprintType)
enum class EUnlockCondition : uint8
{
	EnemyKills UMETA(DisplayMeta = "Enemies to Kill"),
	GameStarts,
	PlayerScore,
	PlayerDeaths,
	UnlockCondition_MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FWeaponUnlockData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWeaponDataAsset>  WeaponAsset = nullptr;

	UPROPERTY(EditAnywhere)
	bool bUnlockedByDefault = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Logo = nullptr;

	UPROPERTY(EditAnywhere, meta=(EditCondition = "!bUnlockedByDefault"))
	EUnlockCondition Condition;

	UPROPERTY(EditAnywhere, meta=(EditCondition = "!bUnlockedByDefault"))
	int32 value;

};

USTRUCT()
struct FWeaponsByCondition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<FName, int32> WeaponValuePairs;
};

UCLASS()
class MYTWINSTICK_API UWeaponUnlockSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void InitialiseUnlockSystem(UDataTable* WeaponsTable);

	UPROPERTY()
	TMap<FName, bool> WeaponUnlockStatus;
	
	TArray<FWeaponsByCondition*> ConditionCollection;
	
	UPROPERTY()
	TArray<int32> ConditionValues;

	void ConditionMet(FName Weapon, EUnlockCondition Condition);

public:
	UFUNCTION(BlueprintCallable)
	void IncreaseCondition(EUnlockCondition Condition, int32 value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FName> GetUnlockedWeapons();
};
