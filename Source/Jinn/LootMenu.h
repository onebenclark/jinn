// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Item.h"
#include "LootMenu.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class JINN_API ULootMenu : public UUserWidget
{
public:
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<class UItem>, int> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MenuIndex;

};
