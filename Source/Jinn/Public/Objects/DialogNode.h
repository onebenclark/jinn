// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class JINN_API UDialogNode : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DialogText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UDialogNode*> Responses;
};
