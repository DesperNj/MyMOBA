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

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// Set up action bindings
	if (EnhancedInputComponent)
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATestMobaPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATestMobaPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATestMobaPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(SetSkillAction, ETriggerEvent::Started, this, &ATestMobaPlayerController::ProceedSkill<ActionType::AIM>);
		EnhancedInputComponent->BindAction(SetSkillAction, ETriggerEvent::Triggered, this, &ATestMobaPlayerController::ProceedSkill<ActionType::AIM>);
		EnhancedInputComponent->BindAction(SetSkillAction, ETriggerEvent::Completed, this, &ATestMobaPlayerController::ProceedSkill<ActionType::CAST>);
	//	EnhancedInputComponent->BindAction(SetSkillAction, ETriggerEvent::Canceled, this, &ATestMobaPlayerController::CastSkill);
		
	}

}

void ATestMobaPlayerController::ProceedSkillLogic(const FInputActionValue& Value, ActionType type)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetCharacter());
	switch (type)
	{
	case AIM:
		lastAimedIndex = Value.Get<float>()-1;
		character->AimSkill(lastAimedIndex);
		break;
	case CAST:
		character->CastSkill(lastAimedIndex);
		break;
	default:
		break;
	}
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
