// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "HealthPotionItem.h"
#include "CreatureAIController.h"

void ACameraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Pawn = Cast<ACameraPawn>(GetPawn());

	HUD = Cast<AGameHUD>(GetHUD());
	HUD->CameraPawn = Pawn;

	SetTickableWhenPaused(true);
	
	LootMenuDisplayed = false;
	InputPause = 0;
}

void ACameraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("CycleParty", IE_Pressed, this, &ACameraPlayerController::CyclePartyMember);
	InputComponent->BindAction("Select", IE_Released, this, &ACameraPlayerController::Select);
	InputComponent->BindAction("Space", IE_Pressed, this, &ACameraPlayerController::Space).bExecuteWhenPaused = true;
	InputComponent->BindAction("LeftFaceButton", IE_Pressed, this, &ACameraPlayerController::LeftFaceButton);
	InputComponent->BindAction("RightFaceButton", IE_Pressed, this, &ACameraPlayerController::RightFaceButton);
	InputComponent->BindAction("TopFaceButton", IE_Pressed, this, &ACameraPlayerController::TopFaceButton);
	InputComponent->BindAction("LeftSpecialButton", IE_Pressed, this, &ACameraPlayerController::LeftSpecialButton);

	InputComponent->BindAxis("MoveForward", this, &ACameraPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACameraPlayerController::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &ACameraPlayerController::PitchCamera).bExecuteWhenPaused = true;
	InputComponent->BindAxis("CameraYaw", this, &ACameraPlayerController::YawCamera).bExecuteWhenPaused = true;
	
}

void ACameraPlayerController::MoveForward(float Value)
{
	if (Pawn->Party[Pawn->PartyIndex]->ActionComponent->ActionAnim != EActionAnim::None || (Pawn->Party[Pawn->PartyIndex]->StatusEffectTag & 1) || InputPause & (uint8)EInputPause::PauseLeftStick)
	{
		Pawn->MovementInput.X = 0.0f;
		return;
	}
	float newValue = FMath::Clamp<float>(Value, -1.0f, 1.0f);
	Pawn->MovementInput.X = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void ACameraPlayerController::MoveRight(float Value)
{
	if (Pawn->Party[Pawn->PartyIndex]->ActionComponent->ActionAnim != EActionAnim::None || (Pawn->Party[Pawn->PartyIndex]->StatusEffectTag & 1) || InputPause & (uint8)EInputPause::PauseLeftStick)
	{
		Pawn->MovementInput.Y = 0.0f;
		return;
	}
	Pawn->MovementInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void ACameraPlayerController::PitchCamera(float Value)
{
	if (InputPause & (uint8)EInputPause::PauseRightStick)
		Pawn->CameraInput.Y = 0.0f;
	else 
		Pawn->CameraInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void ACameraPlayerController::YawCamera(float Value)
{
	if (InputPause & (uint8)EInputPause::PauseRightStick)
		Pawn->CameraInput.X = 0.0f;
	else 
		Pawn->CameraInput.X = Value;
}

void ACameraPlayerController::CyclePartyMember()
{
	if (InputPause & (uint8)EInputPause::PauseCyclePartyMember) return;
	Pawn->Party[Pawn->PartyIndex]->Capsule->SetCollisionProfileName(TEXT("Pawn"));
	Pawn->Party[Pawn->PartyIndex]->IsPlayerControlledMember = false;
	Pawn->PartyIndex = (Pawn->PartyIndex + 1) % Pawn->Party.Num();
	Pawn->SetActorLocation(Pawn->Party[Pawn->PartyIndex]->GetActorLocation());
	Pawn->Party[Pawn->PartyIndex]->Capsule->SetCollisionProfileName(TEXT("PlayerControlled"));
	Pawn->Party[Pawn->PartyIndex]->IsPlayerControlledMember = true;

	HUD->SetPartyIndex(Pawn->PartyIndex);
}

void ACameraPlayerController::Select()
{
	if(InputPause == (uint8)EInputPause::ActionAimingPause)
	{
		ToggleActionAimPause();
		return;
	}
	if(InputPause == (uint8)EInputPause::ActionPlacementPause != 0)
	{
		ToggleActionPlacementPause();
		return;
	}
	if (InputPause & (uint8)EInputPause::PauseFaceButtons) return;
	Pawn->Party[Pawn->PartyIndex]->Target = 0;
	if (!Pawn->ActorToSelect) return;
	UDialogComponent* dialog = Pawn->ActorToSelect->FindComponentByClass<UDialogComponent>();
	Pawn->Party[Pawn->PartyIndex]->Target = Pawn->ActorToSelect;
	
	
}

void ACameraPlayerController::Space()
{
	
}

void ACameraPlayerController::LeftFaceButton()
{
	if (InputPause & (uint8)EInputPause::PauseFaceButtons) return;
	ACreature* ControlledCreature = Pawn->Party[Pawn->PartyIndex];
	ControlledCreature->ActionComponent->ExecuteLeftFaceButtonAction(ControlledCreature, ControlledCreature->Target);
}

void ACameraPlayerController::RightFaceButton()
{
	if (InputPause & (uint8)EInputPause::PauseFaceButtons) return;
	ACreature* ControlledCreature = Pawn->Party[Pawn->PartyIndex];
	ControlledCreature->ActionComponent->ExecuteRightFaceButtonAction(ControlledCreature, ControlledCreature->Target);
}

void ACameraPlayerController::TopFaceButton()
{
	if (InputPause & (uint8)EInputPause::PauseFaceButtons) return;
	ACreature* ControlledCreature = Pawn->Party[Pawn->PartyIndex];
	ControlledCreature->ActionComponent->ExecuteTopFaceButtonAction(ControlledCreature, ControlledCreature->Target);
}

void ACameraPlayerController::LeftSpecialButton()
{
	if (InputPause == (uint8)EInputPause::MenuPause)
	{
		AWorldSettings* worldSettings = GetWorldSettings();
		InputPause = 0;
		HUD->RemovePartyMenu();
		worldSettings->SetTimeDilation(1.0f);
	}
	else
	{
		AWorldSettings* worldSettings = GetWorldSettings();
		InputPause = (uint8)EInputPause::MenuPause;
		HUD->DisplayPartyMenu();
		worldSettings->SetTimeDilation(0.0f);
		Pawn->CustomTimeDilation = 1.0f;
	}
}

void ACameraPlayerController::DisplayLootMenu(ALootDrop* Loot)
{
	AWorldSettings* worldSettings = GetWorldSettings();
	InputPause = (uint8)EInputPause::MenuPause;
	HUD->DisplayLootMenu(Loot);
	worldSettings->SetTimeDilation(0.0f);
	Pawn->CustomTimeDilation = 1.0f;
	LootMenuDisplayed = true;
}

void ACameraPlayerController::RemoveLootMenu()
{
	AWorldSettings* worldSettings = GetWorldSettings();
	InputPause = 0;
	HUD->RemoveLootMenu();
	Pawn->Party[Pawn->PartyIndex]->Target = 0;
	worldSettings->SetTimeDilation(1.0f);
	LootMenuDisplayed = false;
	Pawn->ActorToSelect = 0;
}

void ACameraPlayerController::TakeLoot(TSubclassOf<class UItem> ItemClass, int Quantity)
{
	if (Pawn->Inventory.Contains(ItemClass)) Pawn->Inventory[ItemClass] += Quantity;
	else Pawn->Inventory.Add(ItemClass, Quantity);
}

void ACameraPlayerController::ToggleActionAimPause()
{
	AWorldSettings* worldSettings = GetWorldSettings();
	if (InputPause != (uint8)EInputPause::ActionAimingPause)
	{
		InputPause = (uint8)EInputPause::ActionAimingPause;
		worldSettings->SetTimeDilation(0.0f);
		Pawn->CustomTimeDilation = 1.0f;
		Pawn->ActionAimingWidget->SetVisibility(true);
	}
	else
	{
		InputPause = 0;
		worldSettings->SetTimeDilation(1.0f);
		Pawn->ActionAimingWidget->SetVisibility(false);
		Pawn->Party[Pawn->PartyIndex]->ActionComponent->QueuedAction->Direction = Pawn->Camera->GetForwardVector().GetSafeNormal2D();
		Pawn->Party[Pawn->PartyIndex]->ActionComponent->QueuedAction->Execute(Pawn->Party[Pawn->PartyIndex], Pawn->Party[Pawn->PartyIndex]->Target);
	}
}

void ACameraPlayerController::ToggleActionPlacementPause()
{
	if (!Pawn->Party[Pawn->PartyIndex]->ActionComponent->QueuedAction)
	{
		return;
	}
	if (InputPause != (uint8)EInputPause::ActionPlacementPause)
	{
		InputPause = (uint8)EInputPause::ActionPlacementPause;
		AWorldSettings* worldSettings = GetWorldSettings();

		worldSettings->SetTimeDilation(0.0f);
		Pawn->CustomTimeDilation = 10000.0f;

		FActorSpawnParameters params;
		params.Owner = Pawn;
		UWorld* world = GetWorld();
		if (!world) return;
		FVector loc = Pawn->GetActorLocation();
		FRotator rot = Pawn->GetActorRotation();
		Pawn->ActionPlacementActor = Cast<AActionPlacementActor>(world->SpawnActor(Pawn->ActionPlacementActorClass, &loc, &rot, params));
		Pawn->ActionPlacementActor->CustomTimeDilation = 10000.0f;
		
	}
	else
	{
		InputPause = 0;
		AWorldSettings* worldSettings = GetWorldSettings();
		worldSettings->SetTimeDilation(1.0f);
		Pawn->CustomTimeDilation = 1.0f;
		//if(Pawn->ActionPlacementActor)Pawn->ActionPlacementActor->Destroy();
		Pawn->ActionPlacementActor->ActionPlacementWidget->SetVisibility(false);
		FVector direction = Pawn->ActionPlacementActor->GetActorLocation() - Pawn->Party[Pawn->PartyIndex]->GetActorLocation();
		Pawn->Party[Pawn->PartyIndex]->ActionComponent->QueuedAction->Direction = direction.GetSafeNormal2D();
		Pawn->Party[Pawn->PartyIndex]->ActionComponent->QueuedAction->Execute(Pawn->Party[Pawn->PartyIndex], Pawn->ActionPlacementActor);
	}
}

void ACameraPlayerController::DisplayDialogWidget(UDialogNode* Dialog)
{
	HUD->DisplayDialogWidget(Dialog);
	InputPause = (uint8)EInputPause::DialogPause;
}

void ACameraPlayerController::RemoveDialogWidget()
{
	HUD->RemoveDialogWidget();
	InputPause = 0;
}