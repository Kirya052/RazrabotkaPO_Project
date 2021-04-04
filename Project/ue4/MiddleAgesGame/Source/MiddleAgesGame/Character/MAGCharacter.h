// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MAGCharacter.generated.h"

UCLASS(Abstract, NotBlueprintable)
class MIDDLEAGESGAME_API AMAGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void LookUp(float Value) {};
	virtual void Turn(float Value) {};

	virtual void ChangeCrouchState();
};