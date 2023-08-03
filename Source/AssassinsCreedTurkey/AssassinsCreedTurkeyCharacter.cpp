// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssassinsCreedTurkeyCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AAssassinsCreedTurkeyCharacter

AAssassinsCreedTurkeyCharacter::AAssassinsCreedTurkeyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAssassinsCreedTurkeyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAssassinsCreedTurkeyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAssassinsCreedTurkeyCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAssassinsCreedTurkeyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAssassinsCreedTurkeyCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AAssassinsCreedTurkeyCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AAssassinsCreedTurkeyCharacter::Walk);
}

void AAssassinsCreedTurkeyCharacter::TakeDamage_Implementation(float Damage, AActor* DamagetActor, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauses)
{
	Hearth -= Damage;
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Hearth: %f"), Hearth));
}
void AAssassinsCreedTurkeyCharacter::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}
void AAssassinsCreedTurkeyCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = 200;
}
void AAssassinsCreedTurkeyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Trace();
}
void AAssassinsCreedTurkeyCharacter::Trace()
{
	FVector StartTraceLine = GetActorLocation();
	FVector EndTraceLine = GetActorForwardVector() * TraceRadius + StartTraceLine;
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTraceLine, EndTraceLine, ECollisionChannel::ECC_Camera, Param);
	DrawDebugLine(GetWorld(), StartTraceLine, EndTraceLine, FColor::Red);
	if (HitResult.GetActor())
	{
		FString Actor = HitResult.GetActor()->GetName();
		float ActorDis = HitResult.Distance;
		if (Actor == "AI_2" && ActorDis <= 50)
		{
			GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Green, TEXT("Kilicini Cek Bire"));
		}
	}
}

void AAssassinsCreedTurkeyCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAssassinsCreedTurkeyCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAssassinsCreedTurkeyCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAssassinsCreedTurkeyCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
