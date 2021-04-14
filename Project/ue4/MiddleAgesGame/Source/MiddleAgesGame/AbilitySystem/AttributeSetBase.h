// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHeathChangeDelegate, float, Health, float, MaxHealth);

UCLASS()
class MIDDLEAGESGAME_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAttributeSetBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet base")
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet base")
	FGameplayAttributeData MaxHealth;

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	FOnHeathChangeDelegate OnHealthChange;
};
