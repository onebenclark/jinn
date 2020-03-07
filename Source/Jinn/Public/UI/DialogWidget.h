// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DialogNode.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class JINN_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    UDialogNode* Dialog;
};
