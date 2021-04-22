// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "../Character/MAGCharacter.h"
#include "../Character/AssasinCharacter.h"

UAttributeSetBase::UAttributeSetBase()
	:Health(200.0f),
	MaxHealth(200.0f),
	Stamina(200.0f),
	MaxStamina(200.0f),
	Mana(200.0f),
	MaxMana(200.0f)
{

}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetBaseValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		AAssasinCharacter* CharacterOwner = Cast<AAssasinCharacter>(GetOwningActor());
		if (CharacterOwner)
		{
			if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
			{
				CharacterOwner->AddGameplayTag(CharacterOwner->FullHealthTag);
			}
			else 
			{
				CharacterOwner->RemoveGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Stamina)))
	{
		Stamina.SetCurrentValue(FMath::Clamp(Stamina.GetCurrentValue(), 0.f, MaxStamina.GetCurrentValue()));
		Stamina.SetBaseValue(FMath::Clamp(Stamina.GetBaseValue(), 0.f, MaxStamina.GetBaseValue()));
		OnStaminaChange.Broadcast(Stamina.GetCurrentValue(), MaxStamina.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetBaseValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

}
