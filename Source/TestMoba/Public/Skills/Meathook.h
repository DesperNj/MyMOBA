// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Skill.h"
#include "Meathook.generated.h"

/**
 * 
 */
UCLASS()
class TESTMOBA_API UMeatHook : public USkill
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float range = 1800.0f;
public:
	UMeatHook();

	void SkillshotLogic(FVector2D target) override;
};
