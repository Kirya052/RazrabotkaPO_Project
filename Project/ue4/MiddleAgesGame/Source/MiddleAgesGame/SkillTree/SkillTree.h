// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/DataTable.h>
#include "SkillTree.generated.h"



UENUM(BlueprintType)
enum class TypeAbilities : uint8
{
	MeleeAttack = 0,
	PlayerStats,
	DistanceAttack,
	AttackMagic
};


USTRUCT(BlueprintType)
struct FAbilities : public FTableRowBase
{
	GENERATED_BODY()

public:
	FAbilities();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	FName AbilityID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	FText NameAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	int32 CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	int32 SkillPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	TypeAbilities TypeAbility = TypeAbilities::MeleeAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree system")
	FText Description;
};

UCLASS()
class MIDDLEAGESGAME_API ASkillTree : public AActor
{
	GENERATED_BODY()
	
};
