// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class JINN_API UHealthPotionItem : public UItem
{
	GENERATED_BODY()
public:
	UHealthPotionItem();

	bool Use(ACreature* Target) override;
};
