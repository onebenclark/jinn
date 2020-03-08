// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "CameraPawn.h"

AGameHUD::AGameHUD()
{
	static ConstructorHelpers::FClassFinder<UPartyUI> partyWidgetBlueprint(TEXT("/Game/UI/bpPartyUI"));
	PartyWidgetClass = partyWidgetBlueprint.Class;
	
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PartyWidgetClass == nullptr) return;
	PartyWidget = CreateWidget<UPartyUI>(GetWorld(), PartyWidgetClass);

	if (!PartyWidget) return;

	PartyWidget->Party = CameraPawn->Party;
	PartyWidget->PartyIndex = CameraPawn->PartyIndex;


	PartyWidget->AddToViewport();
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
	
}

void AGameHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGameHUD::SetPartyIndex(int index)
{
	PartyWidget->PartyIndex = index;
}

void AGameHUD::DisplayLootMenu(ALootDrop* LootDrop)
{
	LootMenuWidget = CreateWidget<ULootMenu>(GetWorld(), LootMenuClass);
	LootMenuWidget->LootDrop = LootDrop;
	LootMenuWidget->AddToViewport();
}

void AGameHUD::RemoveLootMenu()
{
	
	LootMenuWidget->RemoveFromParent();
	if (LootMenuWidget->LootDrop->Inventory.Num() == 0) LootMenuWidget->LootDrop->Destroy();
	LootMenuWidget = 0;
}

void AGameHUD::DisplayPartyMenu()
{
	PartyMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PartyMenuWidgetClass);
	PartyMenuWidget->AddToViewport();
}

void AGameHUD::RemovePartyMenu()
{
	PartyMenuWidget->RemoveFromParent();
	PartyMenuWidget = 0;
}

void AGameHUD::DisplayDialogWidget(UDialogNode* Dialog)
{
	DialogWidget = CreateWidget<UDialogWidget>(GetWorld(), DialogWidgetClass);
	DialogWidget->Dialog = Dialog;
	DialogWidget->AddToViewport();
}

void AGameHUD::RemoveDialogWidget()
{
	DialogWidget->RemoveFromParent();
	DialogWidget = 0;
}