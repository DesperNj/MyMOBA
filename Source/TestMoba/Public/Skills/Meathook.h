// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Skill.h"
#include "CableComponent.h"
#include "Components/SplineComponent.h"
#include "Meathook.generated.h"

UCLASS(ClassGroup = (Skills), meta = (BlueprintSpawnableComponent), Blueprintable)
class TESTMOBA_API UMeatHook : public USkill
{
	GENERATED_BODY()
	void SetActiveHook(bool state);
	virtual void BeginPlay() override;
	bool _casting = false;
	float _castTime, _timeBuffer = 0, _distanceToTarget;

	UPROPERTY(VisibleAnywhere)
	USplineComponent* _splineComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _meshComponent;

	UPROPERTY(VisibleAnywhere)
	UCableComponent* _cableComponent;

	FVector _cachedTargetPos;
	bool _firstHit = false, _pulling = false;

	ABaseCharacter* _lastHit;
	UFUNCTION()
		void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UMeatHook();
	void SkillshotLogic(FVector2D target) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
