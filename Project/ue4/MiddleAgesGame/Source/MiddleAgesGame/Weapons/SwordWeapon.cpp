// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordWeapon.h"
#include <Components/SkeletalMeshComponent.h>

// Sets default values
ASwordWeapon::ASwordWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SwordMesh");
	SetRootComponent(SwordMesh);
}

// Called when the game starts or when spawned
void ASwordWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


