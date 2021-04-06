// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"
#include "../Character/AssasinCharacter.h"
#include "InventoryGameState.h"



AInventoryController::AInventoryController()
{
	InventorySlotLimit = 50;
	InventoryWeightLimit = 500;
}

void AInventoryController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &AInventoryController::Interact);
}

void AInventoryController::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
}

int32 AInventoryController::GetInventoryWeight()
{
	int32 Weight = 0;

	for (auto& Item : Inventory)
	{
		Weight += Item.Weight;
	}
	return Weight;
}

bool AInventoryController::AddItemToInventoryByID(FName ID)
{
	AInventoryGameState* GameState = Cast<AInventoryGameState>(GEngine->GetWorld()->GetGameState());
	UDataTable* ItemTable = GameState->GetItemDB();
	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

	if (ItemToAdd)
	{
		// If a Slot- or WeightLimit are not needed remove them in this line
		if (Inventory.Num() < InventorySlotLimit && GetInventoryWeight() + ItemToAdd->Weight <= InventoryWeightLimit)
		{
			Inventory.Add(*ItemToAdd);
			ReloadInventory();
			return true;
		}
	}
	return false;
}


