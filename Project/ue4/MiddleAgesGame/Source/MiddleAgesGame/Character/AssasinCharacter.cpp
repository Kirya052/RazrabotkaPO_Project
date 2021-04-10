// Fill out your copyright notice in the Description page of Project Settings.


#include "AssasinCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Controllers/MAGamePlayerController.h"
#include "Engine/World.h"
#include "../Weapons/SwordWeapon.h"



AAssasinCharacter::AAssasinCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = 1;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
}

void AAssasinCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f)) 
	{
		FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
	}
}

void AAssasinCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector RightVector = YawRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value);
	}
}

void AAssasinCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AAssasinCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AAssasinCharacter::Attack()
{
	bIsAttack = true;
}

void AAssasinCharacter::AttackEnd()
{
	bIsAttack = false;
}

void AAssasinCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckForInteractables();
}

void AAssasinCharacter::CheckForInteractables()
{
	// Create a LineTrace to check for a hit
	FHitResult HitResult;

	int32 Range = 500;
	FVector StartTrace = CameraComponent->GetComponentLocation();
	FVector EndTrace = (CameraComponent->GetForwardVector() * Range) + StartTrace;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	AMAGamePlayerController* IController = Cast<AMAGamePlayerController>(GetController());

	if (IController)
	{
		// Check if something is hit
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			// Cast the actor to AInteractable
			AInteractable* Interactable = Cast<AInteractable>(HitResult.GetActor());
			// If the cast is successful
			if (Interactable)
			{
				IController->CurrentInteractable = Interactable;
				return;
			}
		}

		IController->CurrentInteractable = nullptr;
	}
}


void AAssasinCharacter::SpawnWeapon()
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
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		Sword->AttachToComponent(GetMesh(), AttachmentRules, "SwordSocket");
		bIsWeaponSpawned = true;
		EquipedWeapon = Sword;
		bIsWeaponEquiped = true;
	}

}


void AAssasinCharacter::EquipWeapon()
{
	if (!bIsWeaponSpawned)
	{
		return;
	}
	if (bIsWeaponEquiped)
	{
		SocketName = "EquipedSocket";
		bIsWeaponEquiped = false;
	}
	else
	{
		SocketName = "SwordSocket";
		bIsWeaponEquiped = true;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	EquipedWeapon->AttachToComponent(GetMesh(), AttachmentRules, SocketName);
}

UAbilitySystemComponent* AAssasinCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AAssasinCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
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

