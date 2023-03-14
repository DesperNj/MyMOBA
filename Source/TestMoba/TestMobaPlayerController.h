// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TestMobaPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;


UENUM(BlueprintType)
enum class KeyInputType : uint8 {
	KI_First UMETA(DisplayName = "First skill"),
	KI_Second UMETA(DisplayName = "Second skill"),
	KI_Third UMETA(DisplayName = "Third skill"),
	KI_Fourth UMETA(DisplayName = "Fourth skill"),
	KI_Fifth UMETA(DisplayName = "Fifth skill"),
	KI_Ult UMETA(DisplayName = "Ultimate skill"),
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SetFirstSkillhAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SetSecondSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SetThirdSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SetFourthSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SetFifthSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SetUltimateSkillAction;

	template<KeyInputType type>
	void CastSkillTemplate() {
		CastSkill(type);
	}

	template<KeyInputType type>
	void AimSkillTemplate() {
		AimSkill(type);
	}
	DECLARE_DELEGATE_OneParam(_inputDelegate, int32);
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void CastSkill(KeyInputType type);
	void AimSkill(KeyInputType type);

private:
	FVector CachedDestination;


	void BindSkillInput(UEnhancedInputComponent* inputComponent, UInputAction* controller, void(ATestMobaPlayerController::* Aim)(), void(ATestMobaPlayerController::* Cast)());

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


