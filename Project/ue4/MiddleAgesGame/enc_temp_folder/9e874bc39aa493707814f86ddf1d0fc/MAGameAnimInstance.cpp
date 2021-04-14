// Fill out your copyright notice in the Description page of Project Settings.


#include "MAGameAnimInstance.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "../AssasinCharacter.h"

void UMAGameAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<AAssasinCharacter>(), TEXT("Can worked only AAssasinCharacter"));
	CachedBaseCharacter = StaticCast<AAssasinCharacter*>(TryGetPawnOwner());
}

void UMAGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CachedBaseCharacter.IsValid())
	{
		return;
	}

	UCharacterMovementComponent* CharacterMovement = CachedBaseCharacter->GetCharacterMovement();
	Speed = CharacterMovement->Velocity.Size();
	bIsFalling = CharacterMovement->IsFalling();
	bIsCrouching = CharacterMovement->IsCrouching();
	bIsAttack = CachedBaseCharacter->GetAttack();
}
