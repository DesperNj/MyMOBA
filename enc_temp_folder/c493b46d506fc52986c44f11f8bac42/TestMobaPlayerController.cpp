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
		
		

		BindSkillInput(EnhancedInputComponent, SetFirstSkillhAction, &ATestMobaPlayerController::AimSkillTemplate<KeyInputType::KI_First>, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_First>);

		BindSkillInput(EnhancedInputComponent, SetSecondSkillAction, &ATestMobaPlayerController::AimSkillTemplate<KeyInputType::KI_Second>, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Second>);

		BindSkillInput(EnhancedInputComponent, SetThirdSkillAction, &ATestMobaPlayerController::AimSkillTemplate<KeyInputType::KI_Third>, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Third>);

		BindSkillInput(EnhancedInputComponent, SetFourthSkillAction, &ATestMobaPlayerController::AimSkillTemplate<KeyInputType::KI_Fourth>, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fourth>);

		BindSkillInput(EnhancedInputComponent, SetFifthSkillAction, &ATestMobaPlayerController::AimSkillTemplate<KeyInputType::KI_Fifth>, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Fifth>);

		BindSkillInput(EnhancedInputComponent, SetUltimateSkillAction, &ATestMobaPlayerController::AimSkillTemplate<KeyInputType::KI_Ult>, &ATestMobaPlayerController::CastSkillTemplate<KeyInputType::KI_Ult>);

	}

}

void ATestMobaPlayerController::BindSkillInput(UEnhancedInputComponent* inputComponent, UInputAction* controller, void(ATestMobaPlayerController::* Aim)(), void(ATestMobaPlayerController::* Cast)())
{
	inputComponent->BindAction(controller, ETriggerEvent::Started, this, Aim);
	inputComponent->BindAction(controller, ETriggerEvent::Triggered, this, Aim);
	inputComponent->BindAction(controller, ETriggerEvent::Completed, this, Cast);
	inputComponent->BindAction(controller, ETriggerEvent::Canceled, this, Cast);
}

void ATestMobaPlayerController::CastSkill(KeyInputType type) {
	ABaseCharacter* character = Cast<ABaseCharacter>(GetCharacter());
	if (character != nullptr) {
		switch (type)
		{
		case KeyInputType::KI_First:
			character->CastSkill(0);
			break;
		case KeyInputType::KI_Second:
			character->CastSkill(1);
			break;
		case KeyInputType::KI_Third:
			character->CastSkill(2);
			break;
		case KeyInputType::KI_Ult:
			character->CastSkill(character->GetSkillSetSize()-1);
			break;
		case KeyInputType::KI_Fourth:
			character->CastSkill(4);
			break;
		case KeyInputType::KI_Fifth:
			character->CastSkill(5);
			break;
		default:
			break;
		}
	}
}

void ATestMobaPlayerController::AimSkill(KeyInputType type) {
	ABaseCharacter* character = Cast<ABaseCharacter>(GetCharacter());
	if (character != nullptr) {
		switch (type)
		{
		case KeyInputType::KI_First:
			character->AimSkill(0);
			break;
		case KeyInputType::KI_Second:
			character->AimSkill(1);
			break;
		case KeyInputType::KI_Third:
			character->AimSkill(2);
			break;
		case KeyInputType::KI_Ult:
			character->AimSkill(character->GetSkillSetSize() - 1);
			break;
		case KeyInputType::KI_Fourth:
			character->AimSkill(4);
			break;
		case KeyInputType::KI_Fifth:
			character->AimSkill(5);
			break;
		default:
			break;
		}
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
