// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatusEffect.generated.h"

/**
 * 
 */

class ACreature;

UCLASS(Blueprintable, BlueprintType)
class JINN_API UStatusEffect : public UObject
{
	GENERATED_BODY()
public:
    UStatusEffect();

    UPROPERTY(EditAnywhere)
    float Duration;

    UPROPERTY(EditAnywhere)
    uint8 EffectTag;

    float Time;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void BPEffects(ACreature* AffectedCreature);

    UFUNCTION(BlueprintCallable)
    virtual void Effects(ACreature* AffectedCreature);

    UFUNCTION(BlueprintCallable)
    void Remove(ACreature* AffectedCreature);

};
