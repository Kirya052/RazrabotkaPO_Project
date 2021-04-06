// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class MIDDLEAGESGAME_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractable();

	UFUNCTION(BlueprintNativeEvent)
	void Interact (APlayerController* PlayerController);
	virtual void Interact_Implementation(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	FString GetInteractText() const;

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	FString Action;
};
