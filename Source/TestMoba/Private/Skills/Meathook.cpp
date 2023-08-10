// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/Meathook.h"
#include "Components/CapsuleComponent.h"
#include "TestMoba/Private/BaseCharacter.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/KismetMathLibrary.h"
#include"TestMoba/Public/Characters/Dummy.h"

UMeatHook::UMeatHook() {
	USkill::_manacost = 40;
	USkill::_name = "Meat Hook";
	USkill::_type = SkillType::ST_Skillshot;
	USkill::affectTeammates = true;
	USkill::_range = 900;
	USkill::_projectileSpeed = 95;
	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hook"));
	_meshComponent->SetUsingAbsoluteLocation(true);
	_meshComponent->SetUsingAbsoluteRotation(true);
	_cableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("Chain"));
	_splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplinePath"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Meshes/SkillsContent/Hook"));
	if (CubeVisualAsset.Succeeded()) {
		_meshComponent->SetStaticMesh(CubeVisualAsset.Object);
	}
	_cableComponent->CableLength = 0.0f;
	_cableComponent->NumSegments = 3;
	_cableComponent->SubstepTime = 0.0f;
	_castTime = _range / (_projectileSpeed*10);
	_splineComponent->ReparamStepsPerSegment = _projectileSpeed;
	_splineComponent->Duration = _castTime;
	_splineComponent->SetClosedLoop(false);	
	FScriptDelegate MyScript;
	MyScript.BindUFunction(this, "OnOverlapBegin");
	_meshComponent->OnComponentBeginOverlap.Add(MyScript);
	_meshComponent->Deactivate();
	SetActiveHook(false);
}

void UMeatHook::SetActiveHook(bool state)
{
	_meshComponent->bUseDefaultCollision = !state;
	_meshComponent->SetVisibility(state);
	_meshComponent->SetActive(state);
	_cableComponent->SetVisibility(state);
	_splineComponent->SetActive(state);
}

void UMeatHook::BeginPlay() {
	Super::BeginPlay();
	if (_owner) {
		_splineComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		_splineComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		_meshComponent->AttachToComponent(_splineComponent,FAttachmentTransformRules::KeepRelativeTransform);
		_meshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		_cableComponent->AttachToComponent(_meshComponent, FAttachmentTransformRules::KeepRelativeTransform);
		_cableComponent->SetRelativeLocation(_meshComponent->GetSocketByName(TEXT("Chain"))->RelativeLocation);
		_cableComponent->SetAttachEndTo(_owner, TEXT("Mesh"), TEXT("RHand"));
		_cableComponent->EndLocation = FVector(0, 0, 0);
		
	}
}

void UMeatHook::SkillshotLogic(FVector2D target)
{
	FVector PlayerPos = FVector(_owner->GetActorLocation().X, _owner->GetActorLocation().Y, _splineComponent->GetWorldLocationAtSplinePoint(0).Z);
	FVector CursorPos = FVector(target.X, target.Y, _splineComponent->GetWorldLocationAtSplinePoint(0).Z);
	_cachedTargetPos = ((CursorPos - PlayerPos).GetSafeNormal() * _range) + PlayerPos;
	
	_casting = true;
	_timeBuffer = 0;
	SetActiveHook(true);
}

void UMeatHook::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (_casting) {
		if (!_pulling && _timeBuffer <= _castTime) {
			//Push
			_timeBuffer += DeltaTime;
		}
		else {
			//Pull
			_timeBuffer -= DeltaTime;
		}
		if (_timeBuffer <=0 || (_distanceToTarget<=100 && _firstHit)) {
			_distanceToTarget = 0;
			_casting = false;
			_firstHit = false;
			_pulling = false;
			SetActiveHook(false);
		}
		if (_timeBuffer >= _castTime) {
			_pulling = true;
		}
		_splineComponent->SetWorldLocationAtSplinePoint(1, _cachedTargetPos);
		_meshComponent->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(_splineComponent->GetWorldLocationAtSplinePoint(0), _cachedTargetPos));
		_meshComponent->SetWorldLocation(_splineComponent->GetLocationAtTime(_timeBuffer, ESplineCoordinateSpace::Type::World));
		if (_firstHit) {
			_lastHit->SetActorLocation(_meshComponent->GetRelativeLocation());
			_distanceToTarget = _owner->GetDistanceTo(_lastHit);
		}
	}
}

void UMeatHook::OnOverlapBegin(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* HitTarget = Cast<ABaseCharacter>(OtherComp);
	if (HitTarget) {
		if (HitTarget != _owner && !_firstHit) {
			_cachedTargetPos = HitTarget->GetActorLocation();
			_lastHit = HitTarget;
			_firstHit = true;
			_pulling = true;
		}
	}
}
