// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Vitality = 5;
	Agility = 5;
	Willpower = 5;
	Intelligence = 5;

	Accuracy = 70;
	EffectiveAccuracy = Accuracy;

	Experience = 0;
	Level = 1;
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	MaxHealth = (Vitality * 5.0f) + (Willpower * 5.0f) + 10.0f;
	MaxWill = (Willpower * 8.0f) + 10.0f;
	MaxStamina = (Vitality * 8.0f) + 10.0f;
	Health = MaxHealth;
	Will = 0.0f;
	Stamina = MaxStamina;
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Will > 0.0f)
	{
		Will -= DeltaTime * 2.0f;
		if (Will < 0.0f) Will = 0.0f;
	}
	// ...
}

float UStatsComponent::GetHealthPercentage()
{
	return Health / MaxHealth;
}

float UStatsComponent::GetWillPercentage()
{
	return Will / MaxWill;
}

float UStatsComponent::GetStaminaPercentage()
{
	return Stamina / MaxStamina;
}

float UStatsComponent::GetXPProgressPercentage()
{
	if (Level > 11) return 1.0f;
	float progress = Experience - GetLastLevelThreshold();
	float threshold = GetNextLevelThreshold() - GetLastLevelThreshold();
	return  progress / threshold;
}

void UStatsComponent::AddExperience(float AddedExperience)
{
	Experience += AddedExperience;
	if (Level > 11) return;
	if (Experience > GetNextLevelThreshold()) LevelUp();
}

float UStatsComponent::GetNextLevelThreshold()
{
	switch (Level)
	{
	case 1:
		return 100.0f;
	case 2:
		return 250.0f;
	case 3:
		return 450.0f;
	case 4:
		return 800.0f;
	case 5:
		return 1350.0f;
	case 6:
		return 2050.0f;
	case 7:
		return 3100.0f;
	case 8:
		return 4600.0f;
	case 9:
		return 6800.0f;
	case 10:
		return 10000.0f;
	default:
		return -1;
	}
}

float UStatsComponent::GetLastLevelThreshold()
{
	switch (Level)
	{
	case 1:
		return 0.0f;
	case 2:
		return 100.0f;
	case 3:
		return 250.0f;
	case 4:
		return 450.0f;
	case 5:
		return 800.0f;
	case 6:
		return 1350.0f;
	case 7:
		return 2050.0f;
	case 8:
		return 3100.0f;
	case 9:
		return 4600.0f;
	case 10:
		return 6800.0f;	
	default:
		return -1.0f;
	}
}

void UStatsComponent::LevelUp()
{
	Level++;
}