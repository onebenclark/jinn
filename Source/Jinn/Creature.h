// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"

#include "Item.h"
#include "LootDrop.h"
#include "ActionComponent.h"
#include "StatsComponent.h"
#include "CreatureMovementComponent.h"
#include "Creature.generated.h"

class ACameraPawn;

UENUM(BlueprintType)
enum class EAllegiance : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName="Enemy")
};

UENUM(BlueprintType)
enum class EState : uint8
{
	Passive UMETA(DisplayName = "Passive"),
	Agro UMETA(DisplayName = "Agro"),
	Inactive UMETA(DisplayName = "Inactive"),
	Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class JINN_API ACreature : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UActionComponent* ActionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStatsComponent* StatsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* MeshComponent;

	class UCreatureMovementComponent* MovementComponent;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPartyMember;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPlayerControlledMember;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAllegiance Allegiance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraPawn* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XPWorth;

	UFUNCTION(BlueprintCallable)
	bool IsCloseToPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DeathTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UItem* LeftHandEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UItem* RightHandEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UItem* TorsoEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UItem* LegsEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UItem* HeadEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<class UItem>, int> ItemsToDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ALootDrop> DropClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALootDrop* Pickup;
};
