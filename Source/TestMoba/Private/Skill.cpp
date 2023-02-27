// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"

void ASkill::ReloatSkill(float deltaTime) {
	_reloadTime > 0.0 ? _reloadTime -= deltaTime : _reloadTime -= 0;
}