#include "CryptRaiderCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACryptRaiderCharacter::ACryptRaiderCharacter()
{
	bHasRifle = false;
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	SetupFirstPersonCamera();
	SetupMesh1P();
}

void ACryptRaiderCharacter::SetupFirstPersonCamera()
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void ACryptRaiderCharacter::SetupMesh1P()
{
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void ACryptRaiderCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACryptRaiderCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACryptRaiderCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACryptRaiderCharacter::Look);
	}
}

void ACryptRaiderCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector{ Value.Get<FVector2D>() };

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ACryptRaiderCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector{ Value.Get<FVector2D>() };

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACryptRaiderCharacter::SetHasRifle(bool bValue)
{
	bHasRifle = bValue;
}

bool ACryptRaiderCharacter::GetHasRifle() const
{
	return bHasRifle;
}

USkeletalMeshComponent* ACryptRaiderCharacter::GetMesh1P() const
{
	return Mesh1P;
}

UCameraComponent* ACryptRaiderCharacter::GetFirstPersonCameraComponent() const
{
	return FirstPersonCameraComponent;
}
