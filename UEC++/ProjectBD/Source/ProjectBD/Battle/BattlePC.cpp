// Fill out your copyright notice in the Description page of Project Settings.

#include "BattlePC.h"
#include "Basic/BasicPCM.h"
#include "ConstructorHelpers.h"
#include "UI/ItemTooltipWidgetBase.h"
#include "UI/InventoryWidgetBase.h"

ABattlePC::ABattlePC()
{
	PlayerCameraManagerClass = ABasicPCM::StaticClass();
}

void ABattlePC::BeginPlay()
{
	S2C_SetupWidget();
}

void ABattlePC::S2C_SetupWidget_Implementation()
{
	FStringClassReference ItemTooltipWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/UI/ItemlTooltipWidget.ItemlTooltipWidget_C'"));
	if (UClass* MyWidgetClass = ItemTooltipWidgetClass.TryLoadClass<UUserWidget>())
	{
		ItemTooltip = Cast<UItemTooltipWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		ItemTooltip->AddToViewport();
		ItemTooltip->SetVisibility(ESlateVisibility::Collapsed);
	}

	FStringClassReference InventoryWidgetClassRef(TEXT("WidgetBlueprint'/Game/Blueprints/UI/InventoryWidget.InventoryWidget_C'"));
	if (UClass* MyWidgetClass = InventoryWidgetClassRef.TryLoadClass<UUserWidget>())
	{
		InventoryWidget = Cast<UInventoryWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ABattlePC::ToggleInventory()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
}



