// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Skill.h"
#include "Dismember.generated.h"

/**
 * 
 */
UCLASS()
class TESTMOBA_API UDismember : public USkill
{
	GENERATED_BODY()
public: 
	UDismember();
private:
	void TargetedLogic(AActor* target) override;
};
