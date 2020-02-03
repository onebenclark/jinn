// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Item.h"
#include "LootDrop.generated.h"

UCLASS()
class JINN_API ALootDrop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootDrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<class UItem>, int> Inventory;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayText;
};
