// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseProjectile.h"
#include "DamageInterface.h"

#include "BaseCharacter.generated.h"


UCLASS(Abstract)
class MYTWINSTICK_API ABaseCharacter : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// Declare our Mapping Context and Input Actions
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
	class UInputAction* FireAction;

	// Base Movement Function to link with movement Input
	void Move(const FInputActionValue& value);

	// Independant Look Functions for Gamepad and Mouse
	void Look(const FInputActionValue& value);

	// My Fire Action
	void Fire();

	class APlayerController* PlayerCon;
	APlayerController* GetPlayerController() { return PlayerCon; }

protected:
	// Forward Declare the SpringArm Component
	UPROPERTY(EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "True"))
	class USpringArmComponent* SpringArm;

	// Forward Declare the Camera Component
	UPROPERTY(EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "True"))
	class UCameraComponent* Camera;

	//The Projectile we wish to spawn
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "True"))
	TSubclassOf<ABaseProjectile> Projectile;

public:
	virtual void ApplyDamage(float Damage) override;
};
