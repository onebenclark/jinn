// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine.h"
#include "Creature.h"
#include "Projectile.h"
#include "PartyUI.h"
#include "Item.h"
#include "SelectionWidget.h"
#include "CameraPawn.generated.h"

UCLASS()
class JINN_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraSpringArm;
	

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<class UItem>, int> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ACreature*> Party;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PartyIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ActorToSelect;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* SelectionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* TargetMarkerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* ActionAimingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FString SelectionWidgetText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D MovementInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D CameraInput;

	UFUNCTION(BlueprintCallable)
	void ApplyXP(float XP);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
