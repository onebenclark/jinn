// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "CreatureMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class JINN_API UCreatureMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()
public:
	void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};
