// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MAGameAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MIDDLEAGESGAME_API UMAGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MAGame AnimInstance")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MAGame AnimInstance")
	bool bIsFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MAGame AnimInstance")
	bool bIsCrouching = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MAGame AnimInstance")
	bool bIsAttack = false;

private:
	TWeakObjectPtr<class AAssasinCharacter> CachedBaseCharacter;
};
