// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatusEffect.generated.h"

/**
 * 
 */

class ACreature;

UENUM(BlueprintType)
enum class EStatusEffectTag : uint8
{
    None = 0 UMETA(DisplayName = "None"),
    Immobile = 1 UMETA(DisplayName = "Immobile"),
    PeriodicHealthChange = 2 UMETA(DisplayName = "Periodic Health Change"),
    Overextended = 4 UMETA(DisplayName = "Overextended"),
    SpeedMod = 8 UMETA(DisplayName = "SpeedMod"),
    Inaccurate = 16 UMETA(DisplayName = "Inaccurate"),
    Panicked = 32 UMETA(DisplayName = "Panicked"),
    Confused = 64 UMETA(DisplayName = "Confused"),
    Ensnared = 3 UMETA(DisplayName = "Ensnared"),
    Stunned = 65 UMETA(DisplayName = "Stunned")
};


UCLASS(Blueprintable, BlueprintType)
class JINN_API UStatusEffect : public UObject
{
	GENERATED_BODY()
public:
    UStatusEffect();


    UPROPERTY(EditAnywhere)
    uint8 NumberOfCharges;

    UPROPERTY(EditAnywhere)
    TArray<EStatusEffectTag> EffectTags;

    //Time Between Effect applications in seconds.
    UPROPERTY(EditAnywhere)
    float Interval;

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
