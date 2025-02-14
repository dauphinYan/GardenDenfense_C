// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "SunWidgetPool.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API USunWidgetPool : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


	void PlaySunSelectedAnimation(FVector2D ActorScreenPosition);
	UUserWidget* GetValidWidget();
protected:
	UFUNCTION()
	void UpdateSunWidgetPosition(float Value);

	UFUNCTION()
	void OnSelectTimelineFinished();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SunImageClass;

	TArray<UUserWidget*> SunWidgets;

	UUserWidget* SunWidget;

	UPROPERTY()
	FTimeline MoveTimeline;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* MoveCurve;

	FOnTimelineFloat MoveFunction;

	FVector2D StartPosition;
	FVector2D EndPosition = FVector2D(25, 25);

	FOnTimelineEvent SelectTimelineFinishedEvent;
};
