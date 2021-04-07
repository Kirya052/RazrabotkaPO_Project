// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../../Inventory/InventoryItem.h"
#include "../../Inventory/Interactable.h"
#include "MAGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MIDDLEAGESGAME_API AMAGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetPawn(APawn* InPawn) override;
	AMAGamePlayerController();

protected:
	virtual void SetupInputComponent() override;
	void Interact();
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void ChangeCrouchState();
	void Jump();

	void Attack();
	void AttackEnd();

	TSoftObjectPtr<class AMAGCharacter> CachedBaseCharacter;

public: 
	UFUNCTION(BlueprintImplementableEvent)
	void ReloadInventory();

	UFUNCTION(BlueprintCallable, Category = "Utils")
	int32 GetInventoryWeight();

	UFUNCTION(BlueprintCallable, Category = "Utils")
	bool AddItemToInventoryByID(FName ID);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AInteractable* CurrentInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventorySlotLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventoryWeightLimit;
};
