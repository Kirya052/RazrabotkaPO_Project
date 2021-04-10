// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"


FAbilities::FAbilities()
{
	this->NameAbility = FText::FromString("No Name");
	this->CharacterLevel = 1;
	this->Description = FText::FromString("No Description");
	this->SkillPoint = 0;
	this->Value = 0;
}
