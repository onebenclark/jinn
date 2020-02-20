// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JINN_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void DecrementActionCooldowns(float DeltaTime);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* The ActionMap lists the available actions.
	 * A map was chosen because both the Class and the Object are need for different reasons.
	 * The Class is needed so that Actions can easily be added in Details panes.
	 * The Object needs to be kept after creation because it stores info needed outside of the 
	 * moment of execution i.e. Cooldown
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<class UAction>, UAction*> ActionMap;

	UAction* QueuedAction;
	
	UFUNCTION(BlueprintCallable)
	void AddAvailableAction(TSubclassOf<class UAction> ActionClass);

	UFUNCTION(BlueprintCallable)
	void ExecuteAction(TSubclassOf<class UAction> ActionClass, ACreature* Caller, AActor* Target);

	UFUNCTION(BlueprintCallable)
	void ExecuteLeftFaceButtonAction(ACreature* Caller, AActor* Target);

	UFUNCTION(BlueprintCallable)
	void ExecuteRightFaceButtonAction(ACreature* Caller, AActor* Target);

	UFUNCTION(BlueprintCallable)
	void ExecuteTopFaceButtonAction(ACreature* Caller, AActor* Target);

	UFUNCTION(BlueprintCallable)
	void ExecuteAttackAction(ACreature* Caller, AActor* Target);

	UFUNCTION(BlueprintCallable)
	void ChangeAttackAction(TSubclassOf<class UAction> NewAttackAction);

	UFUNCTION(BlueprintCallable)
	void HandleQueuedAction();

	//These Action Classes are here to map actions to buttons 
	//by being used as keys in the Action Map.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAction> LeftFaceButtonAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAction> RightFaceButtonAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAction> TopFaceButtonAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionAnim ActionAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AvailableAbilityPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LifePoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MindPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ElementalPoints;

};
