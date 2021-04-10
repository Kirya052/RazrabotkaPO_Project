// Fill out your copyright notice in the Description page of Project Settings.


#include "MAGamePlayerController.h"
#include "../AssasinCharacter.h"
#include "../../Inventory/InventoryGameState.h"

void AMAGamePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<AMAGCharacter>(InPawn);
}


AMAGamePlayerController::AMAGamePlayerController()
{
	InventorySlotLimit = 50;
	InventoryWeightLimit = 500;
}

void AMAGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AMAGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMAGamePlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AMAGamePlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &AMAGamePlayerController::Turn);
	InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AMAGamePlayerController::ChangeCrouchState);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMAGamePlayerController::Jump);
	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AMAGamePlayerController::Attack);
	InputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &AMAGamePlayerController::AttackEnd);
	InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AMAGamePlayerController::Interact);
	InputComponent->BindAction("EquipWeapon", EInputEvent::IE_Pressed, this, &AMAGamePlayerController::EquipWeapon);
	InputComponent->BindAction("SpawnWeapon", EInputEvent::IE_Pressed, this, &AMAGamePlayerController::SpawnWeapon);
}


void AMAGamePlayerController::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
}

void AMAGamePlayerController::MoveForward(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveForward(Value);
	}
}

void AMAGamePlayerController::MoveRight(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveRight(Value);
	}
}

void AMAGamePlayerController::LookUp(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LookUp(Value);
	}
}

void AMAGamePlayerController::Turn(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Turn(Value);
	}
}


void AMAGamePlayerController::ChangeCrouchState()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->ChangeCrouchState();
	}
}

void AMAGamePlayerController::Jump()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Jump();
	}
}

void AMAGamePlayerController::Attack()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Attack();
	}
}

void AMAGamePlayerController::AttackEnd()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->AttackEnd();
	}
}


void AMAGamePlayerController::EquipWeapon()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->EquipWeapon();
	}
}


void AMAGamePlayerController::SpawnWeapon()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->SpawnWeapon();
	}
}

int32 AMAGamePlayerController::GetInventoryWeight()
{
	int32 Weight = 0;

	for (auto& Item : Inventory)
	{
		Weight += Item.Weight;
	}
	return Weight;
}

bool AMAGamePlayerController::AddItemToInventoryByID(FName ID)
{
	AInventoryGameState* GameState = Cast<AInventoryGameState>(GetWorld()->GetGameState());
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
