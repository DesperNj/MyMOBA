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

UCLASS(HideDropdown)
class ASkill : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ASkill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float _reloadTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* _owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString _name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float _cooldown = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float _range = 1800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int _manacost = 25;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float _projectileSpeed= 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		SkillType _type = SkillType::ST_Skillshot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool affectTeammates = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool _isSkillOnCast = false;

	UFUNCTION(BlueprintImplementableEvent)
	void SkillCast(FHitResult _hit);

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
		
};
