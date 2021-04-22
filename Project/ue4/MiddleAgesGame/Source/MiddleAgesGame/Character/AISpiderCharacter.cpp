// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpiderCharacter.h"
#include "AIController.h"
#include "BrainComponent.h"

AAISpiderCharacter::AAISpiderCharacter()
{
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AttributeSetComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBase");

	TeamID = 255;
}

void AAISpiderCharacter::BeginPlay()
{
	Super::BeginPlay();

	AttributeSetComp->OnHealthChange.AddDynamic(this, &AAISpiderCharacter::OnHealthChanged);

	AutoDeterminTeamIDbyControllerType();
}

void AAISpiderCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, Value);
	}
}

void AAISpiderCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector RightVector = YawRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, Value);
	}
}

void AAISpiderCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AAISpiderCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AAISpiderCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UAbilitySystemComponent* AAISpiderCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AAISpiderCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
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

void AAISpiderCharacter::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0.f)
	{
		Dead();
		BP_Die();
		bIsDead = true;
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

bool AAISpiderCharacter::IsOtherHostile(AMAGCharacter* Other)
{
	return TeamID != Other->GetTeamID();
}

void AAISpiderCharacter::Dead()
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}
}
