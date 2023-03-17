// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TestMobaPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;


enum ActionType {
	AIM,
	CAST
};

UCLASS()
class ATestMobaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATestMobaPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SetSkillAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

	UPROPERTY(VisibleAnywhere)
		FVector2D TEST;

	template<ActionType type>
	void ProceedSkill(const FInputActionValue& Value){
		ProceedSkillLogic(Value, type);
	}

	DECLARE_DELEGATE_OneParam(_inputDelegate, int32);
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void ProceedSkillLogic(const FInputActionValue& Value, ActionType type);
private:
	FVector CachedDestination;
	UEnhancedInputComponent* EnhancedInputComponent;
	int lastAimedIndex = 0;
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


