// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "BaseProjectile.h"
#include "HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(100.f);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
C++ Attack Implementation for our attack function,

This function can be overriden by Blueprints to change attack in BP [Event Attack]
Or
Override Attack_Internal() to change attack in C++ [Attack_Internal()]
*/
void ABaseCharacter::Attack_Implementation()
{
	Attack_Internal();
}

void ABaseCharacter::Attack_Internal()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Default Attack - Override Event Attack"), *GetActorNameOrLabel());
}





