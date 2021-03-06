// Fill out your copyright notice in the Description page of Project Settings.


#include "ManPickup.h"
#include "../Character/Controllers/MAGamePlayerController.h"

AManPickup::AManPickup()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = Cast<USceneComponent>(PickupMesh);

	ItemID = FName("No ID");

	Super::Name = "Item";
	Super::Action = "pickup";
}

void AManPickup::Interact_Implementation(APlayerController* PlayerController)
{
	Super::Interact_Implementation(PlayerController);

	AMAGamePlayerController* IController = Cast<AMAGamePlayerController>(PlayerController);
	if (IController->AddItemToInventoryByID(ItemID))
		Destroy();
}
