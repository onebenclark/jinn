// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Engine.h"
#include "GameHUD.h"
#include "Creature.h"
#include "CameraPawn.h"
#include "CameraPlayerController.generated.h"

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
public:
	UPROPERTY(BlueprintReadOnly)
	bool ActionPause;
	UPROPERTY(BlueprintReadOnly)
	bool MenuPause;

	UFUNCTION(BlueprintCallable)
	void DisplayLootMenu(ALootDrop* Loot);

	UFUNCTION(BlueprintCallable)
	void RemoveLootMenu();

	UFUNCTION(BlueprintCallable)
	void TakeLoot(TSubclassOf<class UItem> ItemClass, int Quantity);
};
