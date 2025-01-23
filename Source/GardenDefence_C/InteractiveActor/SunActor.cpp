#include "SunActor.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TimelineComponent.h"
#include "GardenDefence_C/GamePlay/MainGameStateBase.h"

ASunActor::ASunActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	SunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SunMesh"));
	SunMesh->SetupAttachment(RootComponent);
	SunMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SunMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SunMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SunMesh->SetSimulatePhysics(true);
	SunMesh->OnClicked.AddDynamic(this, &ASunActor::MeshOnClicked);
	SunMesh->OnComponentBeginOverlap.AddDynamic(this, &ASunActor::OnBeginOverlap);
}

void ASunActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
	GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState());
}

void ASunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTimeline.TickTimeline(DeltaTime);
}

void ASunActor::MeshOnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	SelectSun();
}

void ASunActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SelectSun();
}

void ASunActor::SelectSun()
{
	GameState = GameState == nullptr ? Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;
	GameState->AddSunValue(SunValue);
	SunMesh->SetHiddenInGame(true);
	SunMesh->SetSimulatePhysics(false);
	SunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (SunImageClass)
	{
		SunWidget = CreateWidget<UUserWidget>(GetWorld(), SunImageClass);
		SunWidget->AddToViewport();
	}
	if (SunWidget)
	{
		FVector2D ActorScreenPosition;
		if (PlayerController && UGameplayStatics::ProjectWorldToScreen(PlayerController, SunMesh->GetComponentLocation(), ActorScreenPosition))
		{
			StartPosition = ActorScreenPosition;

			if (MoveCurve)
			{
				MoveFunction.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ASunActor, UpdateSunWidgetPosition));
				SelectTimelineFinishedEvent.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ASunActor, OnSelectTimelineFinished));
				MoveTimeline.AddInterpFloat(MoveCurve, MoveFunction);
				MoveTimeline.SetTimelineFinishedFunc(SelectTimelineFinishedEvent);
				MoveTimeline.SetLooping(false);
				MoveTimeline.PlayFromStart();
			}
		}
	}
}

void ASunActor::UpdateSunWidgetPosition(float Value)
{
	Value = FMath::Clamp(Value, 0.0f, 1.0f);
	FVector2D CurPosition = FMath::Lerp(StartPosition, EndPosition, Value);
	if (SunWidget)
	{
		SunWidget->SetPositionInViewport(CurPosition, false);
	}
}

void ASunActor::OnSelectTimelineFinished()
{
	if (SunWidget)
	{
		SunWidget->RemoveFromParent();
	}
	Destroy();
}
