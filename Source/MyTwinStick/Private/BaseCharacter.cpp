// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our spring arm component and set its defaults
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArm->SetupAttachment(GetRootComponent());

	SpringArm->TargetArmLength = 800.f;
	SpringArm->ProbeChannel = ECollisionChannel::ECC_Camera;

	// Create our Camera Component and set its defaults
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Default Cam"));
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView = 108.f;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetArrowComponent()->SetHiddenInGame(false); // Show Arrow to show direction our character is facing in

	PlayerCon = Cast<APlayerController>(Controller); // Set the Default value of our 
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup our Enhanced input system to recognise our mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Bind our Input Actions to Actual Events in our Character
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move); // Our Movement Binding
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look); // Our Look Binding
	}
}

// Use the Input Action to Move our Character
void ABaseCharacter::Move(const FInputActionValue& value)
{
	FVector2D movementInput = value.Get<FVector2D>();

	AddMovementInput(FVector(movementInput.Y,movementInput.X,0));
}

// Orientate the Character to look in the direction the gamepad pointed in
void ABaseCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookInput = value.Get<FVector2D>();

	// Smooth rotate our character towards the target location
	FRotator TargetRot = FMath::RInterpTo(GetControlRotation(), FVector(lookInput.Y, lookInput.X, 0).ToOrientationRotator(), GetWorld()->GetDeltaSeconds(), 20.0f);

	Controller->SetControlRotation(TargetRot);
}

