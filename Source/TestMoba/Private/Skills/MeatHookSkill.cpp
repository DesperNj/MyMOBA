// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/MeatHookSkill.h"

AMeatHookSkill::AMeatHookSkill() {
	ASkill::_manacost = 40;
	ASkill::_name = "Meat Hook";
	ASkill::type = SkillType::ST_Skillshot;
	ASkill::affectTeammates = true;
}

void AMeatHookSkill::Cast(FVector2D target)
{
}
