// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayHUD.h"
#include "GardenDefence_C/Widget/UserWidget_MainUI.h"

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