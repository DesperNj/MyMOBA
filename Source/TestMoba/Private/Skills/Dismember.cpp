// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/Dismember.h"
#include "TestMoba/Private/BaseCharacter.h"

UDismember::UDismember() {
	USkill::_manacost = 40;
	USkill::_name = "Dismember";
	USkill::_type = SkillType::ST_Targeted;
	USkill::affectTeammates = false;
}

void UDismember::TargetedLogic(AActor* target) {
	ABaseCharacter* characterTarget = Cast<ABaseCharacter>(target);
	if (characterTarget != NULL) {
		characterTarget->SetActorScale3D(FVector(0, 0, 0));
	}
}