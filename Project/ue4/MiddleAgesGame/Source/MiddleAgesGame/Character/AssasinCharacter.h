// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "MAGCharacter.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AssasinCharacter.generated.h"



UCLASS(Blueprintable)
class MIDDLEAGESGAME_API AAssasinCharacter : public AMAGCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public: 
	AAssasinCharacter();

	virtual void BeginPlay() override;

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;

	virtual void Attack() override;
	virtual void AttackEnd() override;

	bool GetAttack() { return bIsAttack; }

	virtual void Tick(float DeltaSeconds) override;
	void CheckForInteractables();

	UFUNCTION(BlueprintCallable, Category = "Assasin Weapon")
	virtual void SpawnWeapon() override;

	UFUNCTION(BlueprintCallable, Category = "Assasin weapon")
	virtual void EquipWeapon() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USpringArmComponent* SpringArmComponent;

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

	UFUNCTION(BlueprintImplementableEvent, Category = "Assasin Character", meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION()
	void OnStaminaChanged(float Stamina, float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, Category = "Assasin Character", meta = (DisplayName = "OnStaminaChanged"))
	void BP_OnStaminaChanged(float Stamina, float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, Category = "Assasin Character", meta = (DisplayName = "Die"))
	void BP_DIe();

	UFUNCTION(BlueprintCallable, Category = "Assasin Character")
	bool IsOtherHostile(AMAGCharacter* Other);

protected:
	uint8 TeamID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Assasin Character")
	bool bIsDead = false;
	
	virtual void Dead() override;
};
