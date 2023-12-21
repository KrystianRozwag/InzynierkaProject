// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSAIProjCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSAIProjGameMode.h"
#include "PHealthComponent.h"

#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// AFPSAIProjCharacter

AFPSAIProjCharacter::AFPSAIProjCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	HealthComponent = CreateDefaultSubobject<UPHealthComponent>("HealthComponent");


}

void AFPSAIProjCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthComponent->OnHealthChanged.AddDynamic(this, &AFPSAIProjCharacter::OnHealthChanged);
}
void AFPSAIProjCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	SetHasRifle(true);
}

//////////////////////////////////////////////////////////////////////////// Input

void AFPSAIProjCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	const APlayerController* PlayerController = GetController<APlayerController>();
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSAIProjCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSAIProjCharacter::Look);
	}
}


void AFPSAIProjCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSAIProjCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSAIProjCharacter::OnHealthChanged(AActor* InstigatorActor, UPHealthComponent* OwningComponent, float NewHealth,
	float Delta)
{
	if(NewHealth<= 0.f && Delta <0.f)
	{
		AFPSAIProjGameMode* GameMode = GetWorld()->GetAuthGameMode<AFPSAIProjGameMode>();
		if (GameMode)
		{
			GameMode->OnActorKilled(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)), InstigatorActor);
		}
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if(PlayerController)
		{
			PlayerController->bEnableClickEvents = 0; //temp fix
			DisableInput(PlayerController); // if player is dead, disabling input
			PlayerController->UnPossess();
		}


	}
}


void AFPSAIProjCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AFPSAIProjCharacter::GetHasRifle()
{
	return bHasRifle;
}