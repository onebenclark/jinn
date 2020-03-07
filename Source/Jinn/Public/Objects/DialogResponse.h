// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogResponse.generated.h"

/**
 * 
 */

class UDialogNode;

UCLASS(Blueprintable, BlueprintType)
class JINN_API UDialogResponse : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FText ResponseText;

	UPROPERTY(BlueprintReadWrite)
	UDialogNode* Dialog;

};
