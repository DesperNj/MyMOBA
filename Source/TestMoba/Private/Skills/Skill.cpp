// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/Skill.h"
#include "TestMoba/Private/BaseCharacter.h"

// Sets default values for this component's properties
USkill::USkill()
{
	_owner = Cast<ABaseCharacter>(GetOwner());
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void USkill::SCast(FHitResult* hit)
{
	if(_reloadTime <= 0){
		switch (_type)
		{
		case SkillType::ST_Passive:
			break;
		case SkillType::ST_Skillshot:
			SkillshotLogic(FVector2D(hit->Location));
			break;
		case SkillType::ST_Area:
			AOELogic(FVector2D(hit->Location));
			break;
		case SkillType::ST_Targeted:
			// ------------------------------------ А ОТУТА ЗРОБИТИ КАСТ ДО ABaseCharacter
			TargetedLogic(hit->GetActor());
			break;
		default:
			break;
		}
		//_reloadTime += _cooldown;
	}
}

// Called when the game starts
void USkill::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void USkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//_reloadTime > 0 ? _reloadTime -= DeltaTime : _reloadTime -= 0;
	_reloadTime = 0.0f;
}

