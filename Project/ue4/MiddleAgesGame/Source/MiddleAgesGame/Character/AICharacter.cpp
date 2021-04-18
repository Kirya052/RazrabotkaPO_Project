// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Controllers/MAGamePlayerController.h"
#include "../Weapons/SwordWeapon.h"
#include "../AbilitySystem/AttributeSetBase.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "BrainComponent.h"



AAICharacter::AAICharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = 1;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("Capsule component");
	CapsuleCollider->SetCapsuleRadius(10.0f);
	CapsuleCollider->SetCapsuleHalfHeight(WeaponCapsuleHeight);
	CapsuleCollider->SetRelativeLocation(FVector::FVector(0.0f, 0.0f, WeaponCapsuleHeight / 2));
	CapsuleCollider->SetupAttachment(GetMesh(), "SwordSocket");

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AttributeSetComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBase");
}


void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AttributeSetComp->OnHealthChange.AddDynamic(this, &AAICharacter::OnHealthChanged);
}

void AAICharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
	}
}

void AAICharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector RightVector = YawRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value);
	}
}

void AAICharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AAICharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AAICharacter::Attack()
{
	bIsAttack = true;
}

void AAICharacter::AttackEnd()
{
	bIsAttack = false;
}

void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AAICharacter::SpawnWeapon()
{
	if (!GetWorld() || bIsWeaponSpawned)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weapon is already spawned"));
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Spawn weapon"));
	ASwordWeapon* Sword = GetWorld()->SpawnActor<ASwordWeapon>(SwordWeapon);
	if (Sword)
	{
		bIsWeaponSpawned = true;
		EquipedWeapon = Sword;
		bIsWeaponEquiped = false;
		AAICharacter::EquipWeapon();
	}

}


void AAICharacter::EquipWeapon()
{
	if (!bIsWeaponSpawned)
	{
		return;
	}
	if (bIsWeaponEquiped)
	{
		SocketName = "EquipedSocket";
		bIsWeaponEquiped = false;
		WeaponCapsuleHeight = 20.0f;
	}
	else
	{
		SocketName = "SwordSocket";
		WeaponCapsuleHeight = 50.0f;
		bIsWeaponEquiped = true;
	}

	CapsuleCollider->SetCapsuleHalfHeight(WeaponCapsuleHeight);
	CapsuleCollider->SetRelativeLocation(FVector(0.0f, 0.0f, WeaponCapsuleHeight / 2));

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	EquipedWeapon->AttachToComponent(GetMesh(), AttachmentRules, SocketName);
}

UAbilitySystemComponent* AAICharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AAICharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (AbilitySystemComp)
	{
		if (HasAuthority() && AbilityToAquire)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void AAICharacter::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0.f)
	{
		bIsDead = true;
		Dead();
		BP_Die();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

bool AAICharacter::IsOtherHostile(AMAGCharacter* Other)
{
	return TeamID != Other->GetTeamID();
}

void AAICharacter::Dead()
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}

}

