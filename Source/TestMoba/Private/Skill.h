// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class SkillType : uint8 {
	ST_Targeted UMETA(DisplayName ="Targeted"),
	ST_Area UMETA(DisplayName = "Area"),
	ST_Skillshot UMETA(DisplayName = "Skillshot"),
	ST_Passive UMETA(DisplayName = "Passive"),
};

UCLASS(Blueprintable,Blueprintable, Category="SkillBase", MinimalAPI)
class ASkill : public AActor
{
	GENERATED_BODY()

	float _reloadTime = 0.0f;
public:
	UPROPERTY(EditAnywhere)
	FString _name = "";

	UPROPERTY(EditAnywhere)
	float _cooldown = 10.0f;

	UPROPERTY(EditAnywhere)
	int _manacost = 25;

	UPROPERTY(EditAnywhere)
	SkillType type = SkillType::ST_Skillshot;

	UPROPERTY(EditAnywhere)
	bool affectTeammates = false;
	
	void ReloatSkill(float deltaTime);
	virtual void Cast(FVector2D target = FVector2D(0.0f,0.0f)) { return; }
};
