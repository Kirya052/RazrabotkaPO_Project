// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAGCharacter.h"
#include "AbilitySystemComponent.h"
#include "../AbilitySystem/AttributeSetBase.h"
#include "AISpiderCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MIDDLEAGESGAME_API AAISpiderCharacter : public AMAGCharacter
{
	GENERATED_BODY()

public:
	AAISpiderCharacter();

	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spider Character")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spider Character")
	class UAttributeSetBase* AttributeSetComp;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Assasin Character")
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI Spider", meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI Spider", meta = (DisplayName = "Die"))
	void BP_Die();

	UFUNCTION(BlueprintCallable, Category = "AI Character")
	bool IsOtherHostile(AMAGCharacter* Other);

protected:
	uint8 TeamID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Character")
	bool bIsDead = false;

	virtual void Dead() override;
};
