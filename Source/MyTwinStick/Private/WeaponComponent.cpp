// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Weapon.h"

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
		Weapon = AWeapon::CreateWeapon(GetOwner(), DefaultWeapon);
	}
	
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/* TO DO:
	*  ADD NAME TO WEAPONS SO IT CAN BE USED TO PRINTS IT
	*/
	if(Weapon != nullptr)
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Cyan, FString::Printf(TEXT("Weapon: %s, Clip: %i"), *Weapon->GetName(), Weapon->GetCurrentClip()));
}

void UWeaponComponent::FireWeapon()
{
	if (Weapon != nullptr)
	{
		Weapon->Fire();
	}
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
	Weapon->Destroy();
	Weapon = newWeapon;
}


