// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Component/SunWidgetPool.h"
#include "GamePlayHUD.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API AGamePlayHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly)
	class UUserWidget_MainUI* MainUI;

	void SelectPlantInSeedBank(int32 Index);
	void CancelSelectPlantInSeedBank();
	void SelectShovel();
	void CancelSelectShovel();
	void OnShopButtonPressed();
	void RefreshBag();
	void UpdateSun();
	void PlaySunSelectedAnimation(FVector2D ActorScreenPosition);

private:
	UPROPERTY(EditDefaultsOnly)
	USunWidgetPool* SunWidgetPool;
};
