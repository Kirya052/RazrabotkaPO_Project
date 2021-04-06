// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ManPickup.generated.h"

/**
 * 
 */
UCLASS()
class MIDDLEAGESGAME_API AManPickup : public AInteractable
{
	GENERATED_BODY()

public:
	AManPickup();

	void Interact_Implementation(APlayerController* PlayerController) override;

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;
};
