// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"
#include "Creature.h"

UStatusEffect::UStatusEffect()
{
	EffectTimes = 0;
	TimeSinceLastEffect = 0.0f;
}

void UStatusEffect::Effects(ACreature* AffectedCreature, float DeltaTime)
{
	TimeSinceLastEffect += DeltaTime;
	if (TimeSinceLastEffect >= Interval)
	{
		BPEffects(AffectedCreature);
		TimeSinceLastEffect = 0.0f;
		EffectTimes++;
		if (EffectTimes == NumberOfCharges)
		Remove(AffectedCreature);
	}
	
}

void UStatusEffect::Remove(ACreature* AffectedCreature)
{
	AffectedCreature->StatusEffects.Remove(this);
}