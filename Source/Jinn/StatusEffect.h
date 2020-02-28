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
    uint8 NumberOfCharges;

    //Time Between Effect applications in seconds.
    UPROPERTY(EditAnywhere)
    float Interval;

    UPROPERTY(EditAnywhere)
    uint8 EffectTag;

    uint8 EffectTimes;
    float TimeSinceLastEffect;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void BPEffects(ACreature* AffectedCreature);

    UFUNCTION(BlueprintCallable)
    virtual void Effects(ACreature* AffectedCreature, float DeltaTime);

    UFUNCTION(BlueprintCallable)
    void Remove(ACreature* AffectedCreature);

};
