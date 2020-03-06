// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JINN_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Will;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite)
	float MaxWill;
	UPROPERTY(BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Accuracy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectiveAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Vitality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Agility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Willpower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Intelligence;

	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage();

	UFUNCTION(BlueprintCallable)
	float GetWillPercentage();

	UFUNCTION(BlueprintCallable)
	float GetStaminaPercentage();

	UFUNCTION(BlueprintCallable)
	float GetXPProgressPercentage();

	UFUNCTION(BlueprintCallable)
	void AddExperience(float AddedExperience);

	UFUNCTION(BlueprintCallable)
	float GetNextLevelThreshold();
private:
	float GetLastLevelThreshold();
	void LevelUp();
};
