// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"
#include "Creature.h"

UStatusEffect::UStatusEffect()
{
	EffectTimes = 0;
	TimeSinceLastEffect = 0.0f;
	EffectTag = 0;
	
	First = true;
}

void UStatusEffect::Effects(ACreature* AffectedCreature, float DeltaTime)
{
	if (EffectTag == 0)
	{
		for (int32 i = 0; i < EffectTags.Num(); i++)
		{
			EffectTag |= (uint8)EffectTags[i];

		}
		AffectedCreature->StatusEffectTag |= EffectTag;
	}

	if (First)
	{
		First = false;
		BPStart(AffectedCreature);
	}

	TimeSinceLastEffect += DeltaTime;
	if (TimeSinceLastEffect >= Interval)
	{
		BPRecurringEffects(AffectedCreature);
		TimeSinceLastEffect = 0.0f;
		EffectTimes++;
		if (EffectTimes == NumberOfCharges)
		{
			BPEnd(AffectedCreature);
			Remove(AffectedCreature);
			return;
		}

	}
}

void UStatusEffect::Remove(ACreature* AffectedCreature)
{
	for (int32 i = 0; i < EffectTags.Num(); i++) AffectedCreature->StatusEffectTag &= ~((uint8)EffectTags[i]);
	AffectedCreature->StatusEffects.Remove(this);
}