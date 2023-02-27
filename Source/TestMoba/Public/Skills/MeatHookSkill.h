// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "MeatHookSkill.generated.h"

/**
 * 
 */
UCLASS()
class TESTMOBA_API AMeatHookSkill : public ASkill
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float range = 1800.0f;
public:
	AMeatHookSkill();
	void Cast(FVector2D target = FVector2D(0.0f, 0.0f)) override;
};
