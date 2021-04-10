// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwordWeapon.generated.h"

UCLASS()
class MIDDLEAGESGAME_API ASwordWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwordWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sword Weapon")
	class USkeletalMeshComponent* SwordMesh;

	virtual void BeginPlay() override;
};
