// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponDataAsset.h"
#include "Weapon.h"
#include "WeaponStats.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultWeapon != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Weapon"));
		Weapon = AWeapon::CreateWeapon(GetOwner(), GetOwner(), DefaultWeapon);
	}
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*
	if (Weapon != nullptr)
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Cyan, FString::Printf(TEXT("Owner: %s, Weapon: %s, Clip: %i"), *GetOwner()->GetActorNameOrLabel(), *Weapon->GetWeaponInfo()->Name.ToString(), Weapon->GetCurrentClip()));
	*/
}


void UWeaponComponent::SetDefaultWeapon(UWeaponDataAsset* newDefaultWeapon)
{
	if (IsValid(newDefaultWeapon))
	{
		UE_LOG(LogTemp, Warning, TEXT("Default Updated"));
		DefaultWeapon = newDefaultWeapon;
	}
}

void UWeaponComponent::FireWeapon()
{
	// Check if we have a weapon equipped
	if (Weapon == nullptr)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("%s: Fire Error - No weapon"), *GetOwner()->GetActorLabel());
#endif
		return;
	}
	Weapon->Fire();
}

void UWeaponComponent::ReloadWeapon()
{
	if (Weapon != nullptr)
	{
		Weapon->Reload();
	}
}

void UWeaponComponent::EquipWeapon(AWeapon* newWeapon)
{
	if(IsValid(Weapon))
		Weapon->Destroy();
	Weapon = newWeapon;
}




