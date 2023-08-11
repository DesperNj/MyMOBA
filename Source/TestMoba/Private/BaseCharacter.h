// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Skill.h"
#include "GameFramework/Character.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "BaseCharacter.generated.h"

class ATestMobaPlayerController;

UCLASS(Blueprintable)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	void AimSkill(int skillPlace);
	void CastSkill(int skillPlace);
	int GetSkillSetSize();
	void LoadCharacterModel(FString name);
	void PostActorCreated() override;

	UPROPERTY(EditAnywhere)
	USkill* sonen;

	//UPROPERTY(EditAnywhere, Instanced)
	//TArray<USkill*> _skillsSet = {};

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<USkill>> _skillsSet = {};
	TArray<USkill*> _skillObjects;

protected:
	UPROPERTY(EditAnywhere)
	FString CharacterID = TEXT("");	

	UPROPERTY(EditAnywhere)
	float _healthPool = 300;

	UPROPERTY(EditAnywhere)
	float _manaPool = 200;

	UPROPERTY(EditAnywhere)
	float _healthRegen = 0.1f;

	UPROPERTY(EditAnywhere)
	float _manaRegen = 0.15f;

	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere)
		ATestMobaPlayerController* _playerController;

	double degree;
	float _rotator;
	FVector2D _mouseNormal;

	FHitResult _hitResult;

		float _health = 300;
		float _mana = 200;
};
