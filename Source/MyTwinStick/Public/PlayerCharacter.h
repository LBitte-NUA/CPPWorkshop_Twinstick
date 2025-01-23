// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class MYTWINSTICK_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Set the Default values for our player character
	APlayerCharacter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: /* Declare our Input Actions & Mappings */

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
		UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
		UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
	UInputAction* FireAction;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "True"))
	UInputAction* InteractAction;

		/* Declare our Input functions */

	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void Interact();


protected: /* Declare our default components */

	// Forward Declare the SpringArm Component
	UPROPERTY(EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "True"))
		class USpringArmComponent* SpringArm;

	// Forward Declare the Camera Component
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "True"))
		class UCameraComponent* Camera;

	
};
