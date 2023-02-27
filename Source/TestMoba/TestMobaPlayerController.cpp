// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestMobaPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TestMobaCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseCharacter.h"

ATestMobaPlayerController::ATestMobaPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATestMobaPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATestMobaPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATestMobaPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATestMobaPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATestMobaPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATestMobaPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATestMobaPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATestMobaPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_First>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_First>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_First>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_First>);

		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Second>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Second>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Second>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Second>);

		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Third>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Third>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Third>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Third>);

		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fourth>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fourth>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fourth>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fourth>);

		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fifth>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fifth>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fifth>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fifth>);

		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Ult>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Ult>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Ult>);
		EnhancedInputComponent->BindAction(SetFirstSkillhAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Ult>);

	}

}

void ATestMobaPlayerController::CastSkill(KeyInputType type) {

}

void ATestMobaPlayerController::AimSkill(KeyInputType type) {

}

void ATestMobaPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATestMobaPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
		auto charr = GetCharacter();
		ABaseCharacter* second = dynamic_cast<ABaseCharacter*>(charr);
		second->CastSkill();
	}
}

void ATestMobaPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATestMobaPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATestMobaPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
