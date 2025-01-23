// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameStateBase.h"
#include "GardenDefence_C/Widget/GamePlayHUD.h"
#include "Kismet/GameplayStatics.h"

void AMainGameStateBase::AddSunValue(float AddValue)
{
	if (AddValue > 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SunSoundWave);
	}
	SunValue += AddValue;
	CharacterHUD = CharacterHUD == nullptr ? Cast<AGamePlayHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()) : CharacterHUD;
	if (CharacterHUD == nullptr) return;
	CharacterHUD->UpdateSun();
}
