// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Fisher.h"
#include "Skills/Dismember.h"
#include "Skills/Meathook.h"

AFisher::AFisher() {
	CharacterID = "Fisher";
	LoadCharacterModel(CharacterID);
	UMeatHook* obj = CreateDefaultSubobject<UMeatHook>(TEXT("MeatHook"));
	_skillsSet.Add(obj);
	obj->_owner = this;
	UDismember* obj2 = CreateDefaultSubobject<UDismember>(TEXT("Dismember"));
	_skillsSet.Add(obj2); 
	obj2->_owner = this;
}