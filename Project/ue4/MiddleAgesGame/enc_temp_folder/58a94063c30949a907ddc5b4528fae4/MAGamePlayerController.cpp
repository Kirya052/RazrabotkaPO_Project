// Fill out your copyright notice in the Description page of Project Settings.


#include "MAGamePlayerController.h"
#include "../MAGCharacter.h"

void AMAGamePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<AMAGCharacter>(InPawn);
}

void AMAGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AMAGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMAGamePlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AMAGamePlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AMAGamePlayerController::Turn);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMAGamePlayerController::Jump);
}

void AMAGamePlayerController::MoveForward(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveForward(Value);
	}
}

void AMAGamePlayerController::MoveRight(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveRight(Value);
	}
}

void AMAGamePlayerController::LookUp(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LookUp(Value);
	}
}

void AMAGamePlayerController::Turn(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Turn(Value);
	}
}

void AMAGamePlayerController::Jump()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Jump();
	}
}
