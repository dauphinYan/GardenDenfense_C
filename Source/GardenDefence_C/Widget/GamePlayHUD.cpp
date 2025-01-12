// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayHUD.h"
#include "GardenDefence_C/Widget/UserWidget_MainUI.h"
#include "GardenDefence_C/Widget/SeedBank/UserWidget_SeedBank.h"

void AGamePlayHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController)
	{
		MainUI = CreateWidget<UUserWidget_MainUI>(PlayerController, MainUIClass);
		MainUI->AddToViewport();
	}
}

void AGamePlayHUD::SelectPlantInSeedBank(int32 Index)
{
	if (MainUI == nullptr) return;
	MainUI->SeedBank->SelectPlantCard(Index);
}

void AGamePlayHUD::CancelSelectPlantInSeedBank()
{
	if (MainUI == nullptr) return;
	MainUI->SeedBank->OnCanceledSelectPlantCard();
}

void AGamePlayHUD::SelectShovel()
{
	if (MainUI == nullptr) return;
	MainUI->SeedBank->OnSelectedShovel();
}

void AGamePlayHUD::CancelSelectShovel()
{
	if (MainUI == nullptr) return;
	MainUI->SeedBank->OnCanceledShovel();
}

void AGamePlayHUD::OnShopButtonPressed()
{
	if (MainUI == nullptr) return;
	MainUI->SetShopVisibility();
}

void AGamePlayHUD::RefreshBag()
{
	if (MainUI == nullptr) return;
	MainUI->RefreshShopBag();
}

void AGamePlayHUD::UpdateSun()
{
	if (MainUI == nullptr) return;
	MainUI->UpdateSun();
}
