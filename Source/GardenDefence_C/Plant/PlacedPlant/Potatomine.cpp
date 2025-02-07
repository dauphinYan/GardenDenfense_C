#include "Potatomine.h"
#include "Kismet/GameplayStatics.h"


void APotatomine::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(PrepareHandle, this, &APotatomine::InitializePopUp, 15.f, false);
}

void APotatomine::InitializePopUp()
{
	if (PopCurve)
	{
		FOnTimelineFloat MoveFunction;
		FOnTimelineEvent MoveFinishedEvent;
		MoveFunction.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(APotatomine, SetPotatomineLocation));
		MoveFinishedEvent.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(APotatomine, OnPopUpEnd));
		PopUpTimeline.AddInterpFloat(PopCurve, MoveFunction);
		PopUpTimeline.SetTimelineFinishedFunc(MoveFinishedEvent);
		PopUpTimeline.SetLooping(false);
		PopUpTimeline.PlayFromStart();
	}
}

void APotatomine::SetPotatomineLocation(float Value)
{
}

void APotatomine::OnPopUpEnd()
{
}
