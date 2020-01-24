// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class ACreature;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Consumable UMETA(DisplayName = "Consumable"),
	Quest UMETA(DisplayName = "Quest")
};


UCLASS(Blueprintable, BlueprintType)
class JINN_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)
	virtual bool Use(ACreature* Target);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool Effects(ACreature*  Target);
};
