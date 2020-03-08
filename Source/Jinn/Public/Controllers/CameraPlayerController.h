// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Engine.h"
#include "GameHUD.h"
#include "Creature.h"
#include "CameraPawn.h"
#include "CameraPlayerController.generated.h"

UENUM()
enum class EInputPause : uint8
{
	PauseFaceButtons = 0b1,
	PauseLeftStick = 0b10,
	PauseRightStick = 0b100,
	PauseCyclePartyMember = 0b1000,
	PauseSpecialButtons = 0b10000,
	MenuPause = 0b11111,
	ActionAimingPause = 0b11011,
	ActionPlacementPause = 0b11001
};

/**
 * 
 */
UCLASS()
class JINN_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

	ACameraPawn* Pawn;

	AGameHUD* HUD;

protected:
	void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PitchCamera(float Value);
	void YawCamera(float Value);
	void CyclePartyMember();
	void Select();
	void Space();

	void LeftFaceButton();
	void RightFaceButton();
	void TopFaceButton();

	void LeftSpecialButton();
public:
	UPROPERTY(BlueprintReadOnly)
	uint8 InputPause;

	UPROPERTY(BlueprintReadOnly)
	bool ActionAimingPause;
	UPROPERTY(BlueprintReadOnly)
	bool ActionPlacementPause;
	UPROPERTY(BlueprintReadOnly)
	bool MenuPause;
	UPROPERTY(BlueprintReadOnly)
	bool LootMenuDisplayed;

	UPROPERTY(BlueprintReadOnly)
	bool DialogPause;

	UFUNCTION(BlueprintCallable)
	void DisplayLootMenu(ALootDrop* Loot);

	UFUNCTION(BlueprintCallable)
	void RemoveLootMenu();

	UFUNCTION(BlueprintCallable)
	void DisplayDialogWidget(UDialogNode* Dialog);

	UFUNCTION(BlueprintCallable)
	void RemoveDialogWidget();

	UFUNCTION(BlueprintCallable)
	void TakeLoot(TSubclassOf<class UItem> ItemClass, int Quantity);

	UFUNCTION(BlueprintCallable)
	void ToggleActionAimPause();

	UFUNCTION(BlueprintCallable)
	void ToggleActionPlacementPause();
};
