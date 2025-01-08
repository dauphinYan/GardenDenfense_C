// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_Shovel.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API UUserWidget_Shovel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void OnSelectedShovel();
	void OnCanceledShovel();
	void SetShovelLocation();

private:
	FTimerHandle ShovelHandle;

	FVector2D ShovelInitialPosition;

	UPROPERTY()
	class AMainPlayerController* PlayerController;
};
