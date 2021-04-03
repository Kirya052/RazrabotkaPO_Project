// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAGCharacter.h"
#include "AssasinCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MIDDLEAGESGAME_API AAssasinCharacter : public AMAGCharacter
{
	GENERATED_BODY()
	
public: 
	AAssasinCharacter();

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USpringArmComponent* SpringArmComponent;
};
