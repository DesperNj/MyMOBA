// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.generated.h"

class ABaseCharacter;

UENUM(BlueprintType)
enum class SkillType : uint8 {
	ST_Targeted UMETA(DisplayName = "Targeted"),
	ST_Area UMETA(DisplayName = "Area"),
	ST_Skillshot UMETA(DisplayName = "Skillshot"),
	ST_Passive UMETA(DisplayName = "Passive"),
	ST_Movement UMETA(DisplayName = "Movement"),
};

UCLASS( ClassGroup=(Skills), meta=(BlueprintSpawnableComponent), Blueprintable)
class USkill : public UActorComponent
{
	GENERATED_BODY()

	float _reloadTime = 0.0f;
public:	
	// Sets default values for this component's properties
	USkill();

	UPROPERTY(EditAnywhere)
		ABaseCharacter* _owner;

	UPROPERTY(EditAnywhere)
		FString _name = "";

	UPROPERTY(EditAnywhere)
		float _cooldown = 10.0f;

	UPROPERTY(EditAnywhere)
		float _range = 1800.0f;

	UPROPERTY(EditAnywhere)
		int _manacost = 25;

	UPROPERTY(VisibleAnywhere)
		float _projectileSpeed= 20;

	UPROPERTY(EditAnywhere)
		SkillType _type = SkillType::ST_Skillshot;

	UPROPERTY(EditAnywhere)
		bool affectTeammates = false;
	void SCast(FHitResult* _hit);

protected:
	virtual void PassiveLogic() { return; }
	virtual void MovementLogic() { return; }
	virtual void SkillshotLogic(FVector2D direction) { return; }
	virtual void AOELogic(FVector2D centreLocation) { return; }
	//--------------------------------------------------- ОТУТА ПОМIНЯТИ НА ABaseCharacter
	virtual void TargetedLogic(AActor* target) { return; }
	
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
