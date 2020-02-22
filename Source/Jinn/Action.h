// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateTypes.h"
#include "Components/ProgressBar.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

class ACreature;

//Enum to distinguish different types of Actions
UENUM(BlueprintType)
enum class EActionType : uint8
{
	Targeted UMETA(DisplayName = "Targeted"),
	Place UMETA(DisplayName = "Place"),
	Directional UMETA(DisplayName = "Directional"),
	Projectile UMETA(DisplayName = "Projectile")
};

UENUM(BlueprintType)
enum class EActionAnim : uint8
{
	None UMETA(DisplayName = "None"),
	Attack UMETA(DisplayName = "Attack"),
	Projectile UMETA(DisplayName = "Projectile"),
	Missle UMETA(DisplayName = "Missle"),
	ElementalBolts UMETA(DisplayName = "ElementalBolts"),
	FrozenWave UMETA(DisplayName = "FrozenWave"),
	Mend UMETA(DisplayName = "Mend")

};

UCLASS(Blueprintable, BlueprintType)
class JINN_API UAction : public UObject
{
	GENERATED_BODY()
public:
	UAction();

	//Name for UI purposes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	//How close to the target the caller must be to Execute the Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	//Cooldowns are capped at 1.0, different cooldown lengths are achieved by different cooldown rates.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionAnim Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* Icon;

	//Some Actions will spawn an actor in the world like a projectile or a summoned creature.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> SpawnedClass;

	UFUNCTION(BlueprintCallable)
	virtual bool Effects();

	//Action Effects is here so that Actions can be written in blueprints.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool ActionEffects(ACreature* Caller, ACreature* Target);

	//Execute must be virtual so that pure c++ Actions don't a unimplemented ActionEffects method.
	UFUNCTION(BlueprintCallable)
	virtual bool Execute(ACreature* Caller, AActor* Target);

	//This Spawn method is here to make spawning easier in blueprints, though it makes easier in general.
	UFUNCTION(BlueprintCallable)
	AActor* Spawn(FVector location, FRotator rotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> ActionIconClass;

private:
	UPROPERTY()
	ACreature* CallingCreature;
	UPROPERTY()
	ACreature* TargetedCreature;
};
