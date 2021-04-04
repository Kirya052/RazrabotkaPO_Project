// Fill out your copyright notice in the Description page of Project Settings.


#include "MAGCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>



void AMAGCharacter::ChangeCrouchState()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}
