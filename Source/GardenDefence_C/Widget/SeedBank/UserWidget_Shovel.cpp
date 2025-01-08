// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_Shovel.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UUserWidget_Shovel::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
	this->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetTimerManager().SetTimer(ShovelHandle, this, &UUserWidget_Shovel::SetShovelLocation, 0.01f, true);
	GetWorld()->GetTimerManager().PauseTimer(ShovelHandle);
}

void UUserWidget_Shovel::OnSelectedShovel()
{
	PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
	if (PlayerController->OperationState == EOperationState::EOS_Shovel)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(ShovelHandle);

	}
}

void UUserWidget_Shovel::OnCanceledShovel()
{
	PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
	if (PlayerController)
	{
		GetWorld()->GetTimerManager().PauseTimer(ShovelHandle);
		PlayerController->OperationState = EOperationState::EOS_Unoccupied;
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUserWidget_Shovel::SetShovelLocation()
{
	PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
	if (PlayerController)
	{
		FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		UE_LOG(LogTemp, Log, TEXT("Mouse Position: X=%f, Y=%f"), MousePosition.X, MousePosition.Y);
		this->SetPositionInViewport(MousePosition);
		this->SetVisibility(ESlateVisibility::Visible);
	}
}
