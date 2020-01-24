// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Creature.h"
#include "PartyUI.generated.h"

/**
 * 
 */
UCLASS()
class JINN_API UPartyUI : public UUserWidget
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ACreature*> Party;

	UPROPERTY(BlueprintReadWrite)
	int PartyIndex;
};
