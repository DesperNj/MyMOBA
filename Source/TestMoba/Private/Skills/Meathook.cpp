// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/Meathook.h"

UMeatHook::UMeatHook() {
	USkill::_manacost = 40;
	USkill::_name = "Meat Hook";
	USkill::_type = SkillType::ST_Skillshot;
	USkill::affectTeammates = true;
}


void UMeatHook::SkillshotLogic(FVector2D target)
{
	
	return;
}