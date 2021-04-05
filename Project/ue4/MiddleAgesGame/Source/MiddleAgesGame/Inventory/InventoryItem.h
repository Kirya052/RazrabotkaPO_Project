// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/DataTable.h>
#include "InventoryItem.generated.h"



USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:
	FInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory system")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory system")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory system")
	int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory system")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory system")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory system")
	FText Description;

	bool operator == (const FInventoryItem& OtherItem) const
	{
		if (ItemID == OtherItem.ItemID)
			return true;
		return false;
	}


};
