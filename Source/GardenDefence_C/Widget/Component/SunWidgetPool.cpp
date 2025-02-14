// Fill out your copyright notice in the Description page of Project Settings.


#include "SunWidgetPool.h"

void USunWidgetPool::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	for (int i = 0; i < 5; i++)
	{
		SunWidgets.Add(CreateWidget<UUserWidget>(this, SunImageClass));
	}
}

void USunWidgetPool::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	MoveTimeline.TickTimeline(InDeltaTime);
}

void USunWidgetPool::PlaySunSelectedAnimation(FVector2D ActorScreenPosition)
{
	SunWidget = GetValidWidget();
	StartPosition = ActorScreenPosition;
	if (SunWidget && MoveCurve)
	{
		MoveFunction.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USunWidgetPool, UpdateSunWidgetPosition));
		SelectTimelineFinishedEvent.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(USunWidgetPool, OnSelectTimelineFinished));
		MoveTimeline.AddInterpFloat(MoveCurve, MoveFunction);
		MoveTimeline.SetTimelineFinishedFunc(SelectTimelineFinishedEvent);
		MoveTimeline.SetLooping(false);
		SunWidget->AddToViewport();
		MoveTimeline.PlayFromStart();
	}
}

UUserWidget* USunWidgetPool::GetValidWidget()
{
	for (int i = 0; i < SunWidgets.Num(); i++)
	{
		if (!SunWidgets[i]->IsInViewport())
		{
			return SunWidgets[i];
		}
	}

	return nullptr;
}

void USunWidgetPool::UpdateSunWidgetPosition(float Value)
{
	Value = FMath::Clamp(Value, 0.0f, 1.0f);
	FVector2D CurPosition = FMath::Lerp(StartPosition, EndPosition, Value);
	if (SunWidget)
	{
		SunWidget->SetPositionInViewport(CurPosition, false);
	}
}

void USunWidgetPool::OnSelectTimelineFinished()
{
	SunWidget->RemoveFromParent();
}


