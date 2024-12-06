// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
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
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetArrowComponent()->SetHiddenInGame(false); // Show the directional arrow for our Character
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move); // Our Movement Binding
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look); // Our Look Binding

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Attack); // Bind Fire action to Attack
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ABaseCharacter::Attack);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ABaseCharacter::Reload); // Bind Reload Action to Reload
	}
}

// Our Movevement Function
void APlayerCharacter::Move(const FInputActionValue& value)
{
	FVector2D movementInput = value.Get<FVector2D>();

	AddMovementInput(FVector(movementInput.Y, movementInput.X, 0));
}

// Our Look Function
void APlayerCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookInput = value.Get<FVector2D>();

	// Smooth rotate our character towards the target location
	FRotator TargetRot = FMath::RInterpTo(GetControlRotation(), FVector(lookInput.Y, lookInput.X, 0).ToOrientationRotator(), GetWorld()->GetDeltaSeconds(), 20.0f);

	// Set the Control rotation to our target rotation
	Controller->SetControlRotation(TargetRot);
}








