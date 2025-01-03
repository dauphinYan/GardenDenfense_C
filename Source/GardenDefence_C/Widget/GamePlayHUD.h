// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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

	UPROPERTY()
	class UUserWidget_MainUI* MainUI;

	void SelectPlantInSeedBank(int32 Index);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainUIClass;
};
