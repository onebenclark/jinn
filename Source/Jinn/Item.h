// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class ACreature;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory"),
	Consumable UMETA(DisplayName = "Consumable"),
	Valuable UMETA(DisplayName = "Valuable"),
	Quest UMETA(DisplayName = "Quest")
};


UCLASS(Blueprintable, BlueprintType)
class JINN_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* Icon;

	UFUNCTION(BlueprintCallable)
	virtual bool Use(ACreature* Target);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool Effects(ACreature*  Target);
};
