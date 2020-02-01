// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

#include "PartyUI.h"
#include "Creature.h"
#include "LootMenu.h"
#include "Item.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class JINN_API AGameHUD : public AHUD
{
	GENERATED_BODY()
protected:
public:
	AGameHUD();
	void BeginPlay() override;
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaTime) override;

	void SetPartyIndex(int index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPartyUI* PartyWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* PartyMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULootMenu* LootMenuWidget;

	UPROPERTY(BlueprintReadOnly)
	ACameraPawn* CameraPawn;

	ACreature* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UPartyUI> PartyWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PartyMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ULootMenu> LootMenuClass;

	UFUNCTION(BlueprintCallable)
	void DisplayLootMenu(TMap<TSubclassOf<class UItem>, int> Inventory);

	UFUNCTION(BlueprintCallable)
	void RemoveLootMenu();
};
