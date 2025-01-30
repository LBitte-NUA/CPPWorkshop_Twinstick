// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponUnlockSubsystem.h"

void UWeaponUnlockSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UDataTable* WeaponsTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/TwinStick/Core/Weapon_Unlock/DT_WeaponUnlocking.DT_WeaponUnlocking'")));

	if (WeaponsTable != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Data Table Found"));
		InitialiseUnlockSystem(WeaponsTable);
	}
}

void UWeaponUnlockSubsystem::Deinitialize()
{
	ConditionCollection.Empty();
}

void UWeaponUnlockSubsystem::InitialiseUnlockSystem(UDataTable* WeaponsTable)
{
	for (int8 i = 0; i < static_cast<int8>(EUnlockCondition::UnlockCondition_MAX); i++)
	{
		ConditionValues.Add(0); // Add Condition value element per Condition
		ConditionCollection.Add(new FWeaponsByCondition); // Add WeaponValue Struct for Every Condition
	}

	TArray<FName> WeaponNames = WeaponsTable->GetRowNames();
	for (auto Weapon : WeaponNames)
	{
		const FWeaponUnlockData* WeaponRow = WeaponsTable->FindRow<FWeaponUnlockData>(Weapon, "");

		WeaponUnlockStatus.Add(Weapon, WeaponRow->bUnlockedByDefault);

		if (WeaponRow->bUnlockedByDefault == false)
		{
			ConditionCollection[static_cast<int8>(WeaponRow->Condition)]->WeaponValuePairs.Add(Weapon, WeaponRow->value);
		}
	}
}

void UWeaponUnlockSubsystem::ConditionMet(FName Weapon, EUnlockCondition Condition)
{
	ConditionCollection[static_cast<int8>(Condition)]->WeaponValuePairs.Remove(Weapon);
	WeaponUnlockStatus.Add(Weapon, true);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Weapon Unlocked: %s"), *Weapon.ToString()));

}

void UWeaponUnlockSubsystem::IncreaseCondition(EUnlockCondition Condition, int32 value)
{
	ConditionValues[static_cast<int8>(Condition)] += value;

	for (auto WeaponValuePair : ConditionCollection[static_cast<int8>(Condition)]->WeaponValuePairs)
	{
		if (WeaponValuePair.Value <= ConditionValues[static_cast<int8>(Condition)])
		{
			ConditionMet(WeaponValuePair.Key, Condition);
			break;
		}
	}
}

TArray<FName> UWeaponUnlockSubsystem::GetUnlockedWeapons()
{
	TArray<FName> OutWeps;
	for (auto weapon : WeaponUnlockStatus)
	{
		if (weapon.Value == true)
		{
			OutWeps.Add(weapon.Key);
		}
	}
	return OutWeps;
}
