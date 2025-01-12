// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameStateBase.h"
#include "GardenDefence_C/Widget/GamePlayHUD.h"

void AMainGameStateBase::AddSunValue(float AddValue)
{
	SunValue += AddValue;
	CharacterHUD = CharacterHUD == nullptr ? Cast<AGamePlayHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()) : CharacterHUD;
	if (CharacterHUD == nullptr) return;
	CharacterHUD->UpdateSun();
}
