#include "Skills/Skill.h"
#include "TestMoba/Private/BaseCharacter.h"

ASkill::ASkill()
{
	SetActorTickEnabled(true);	
}

void ASkill::BeginPlay()
{
	//_owner = GetOwner();
	Super::BeginPlay();	
}

void ASkill::PostActorCreated()
{
	_owner = GetParentActor();
}

void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//_owner = GetOwner();
	//_reloadTime > 0 ? _reloadTime -= DeltaTime : _reloadTime -= 0;
	_reloadTime = 0.0f;
}

