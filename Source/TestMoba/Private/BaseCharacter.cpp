// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Skills/Meathook.h"
#include "Skills/Dismember.h"
#include "../TestMobaPlayerController.h"
#include "TestMoba/TestMobaGameMode.h"
#include "Materials/Material.h"
#include "Engine/World.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set size for player capsule and another adjustments
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight())));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	//Setting up model

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;	

	_playerController = Cast<ATestMobaPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ABaseCharacter::CastSkill(int skillPlace) {
	if (_skillsSet.IsValidIndex(skillPlace)&& _playerController != NULL) {
		_playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_PhysicsBody, true, _hitResult);
		_skillsSet[skillPlace]->SCast(&_hitResult);
	}
}

void ABaseCharacter::AimSkill(int skillPlace) {
	if (_skillsSet.IsValidIndex(skillPlace) && _playerController != NULL) {
		_playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_PhysicsBody, true, _hitResult);

		_mouseNormal = (FVector2D(_hitResult.Location) - FVector2D(GetActorLocation())).GetSafeNormal();
		auto some = FMath::Sign(_mouseNormal.X);
		degree = FMath::Acos(FVector2D::DotProduct(FVector2D(1, 0), FVector2D(_mouseNormal.Y, _mouseNormal.X)));
		some > 0 ? _rotator = -degree : _rotator = degree;

		switch (_skillsSet[skillPlace]->_type)
		{
		case SkillType::ST_Passive:

			break;
		case SkillType::ST_Skillshot:
			
			break;
		case SkillType::ST_Area:
			
			break;
		case SkillType::ST_Targeted:
			
			break;
		default:
			break;
		}
	}
		
	
}

int ABaseCharacter::GetSkillSetSize()
{
	return _skillsSet.Num();
}

void ABaseCharacter::LoadCharacterModel(FString name)
{
	FString path = "/Game/Characters/" + name + "/Meshes/" + name;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(*path);
	if (meshAsset.Object != nullptr) {
		GetMesh()->SetSkeletalMeshAsset(meshAsset.Object);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Player stats handler
	_health < _healthPool ? _health += (_healthRegen * DeltaTime) : _health +=0 ;
	_mana < _manaPool ? _mana += (_manaRegen * DeltaTime) : _mana += 0;
	if (_health > _healthPool) {
		_health = _healthPool;
	}
	if (_mana > _manaPool) {
		_mana = _manaPool;
	}
}
