// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actor_PlacedPlant.h"
#include "Components/TimelineComponent.h"
#include "Potatomine.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API APotatomine : public AActor_PlacedPlant
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	FTimerHandle PrepareHandle;
	FTimeline PopUpTimeline;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* PopCurve;

	void InitializePopUp();
	void SetPotatomineLocation(float Value);
	void OnPopUpEnd();
};
