// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAGCharacter.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MIDDLEAGESGAME_API AAICharacter : public AMAGCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAICharacter();

	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

	virtual void Attack() override;
	virtual void AttackEnd() override;

	bool GetAttack() { return bIsAttack; }

	virtual void Tick(float DeltaSeconds) override;

	virtual void SpawnWeapon() override;
	virtual void EquipWeapon() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Attack")
	bool bIsAttack = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class ASwordWeapon> SwordWeapon;

	UPROPERTY(EditAnywhere, Category = "EquipWeapon")
	class ASwordWeapon* EquipedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipWeapon")
	class UCapsuleComponent* CapsuleCollider;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Assasin Character")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Assasin Character")
	class UAttributeSetBase* AttributeSetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Collision")
	float WeaponCapsuleHeight = 20.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Assasin Character")
	bool bIsWeaponSpawned = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Assasin Character")
	bool bIsWeaponEquiped = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Assasin Character")
	FName SocketName = "SwordSocket";

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Assasin Character")
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI Character", meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI Character", meta = (DisplayName = "Die"))
	void BP_Die();
};
