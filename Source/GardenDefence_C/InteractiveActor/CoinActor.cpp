#include "CoinActor.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GardenDefence_C/FunctionLibrary/FunctionUI.h"

ACoinActor::ACoinActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	CoinMesh->SetupAttachment(RootComponent);
	CoinMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CoinMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CoinMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CoinMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CoinMesh->SetSimulatePhysics(true);
	CoinMesh->OnClicked.AddDynamic(this, &ACoinActor::MeshOnClicked);
	CoinMesh->OnComponentBeginOverlap.AddDynamic(this, &ACoinActor::OnBeginOverlap);
}

void ACoinActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
}

void ACoinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTimeline.TickTimeline(DeltaTime);
}

void ACoinActor::UpdateCoinPosition(float Value)
{
	Value = FMath::Clamp(Value, 0.0f, 1.0f);
	FVector2D CurPosition = FMath::Lerp(StartPosition, EndPosition, Value);
	if (CoinWidget)
	{
		CoinWidget->SetPositionInViewport(CurPosition, false);
	}
}

void ACoinActor::OnSelectTimelineFinished()
{
	if (CoinWidget)
	{
		CoinWidget->RemoveFromParent();
	}
	Destroy();
}

void ACoinActor::MeshOnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	OnSelect();
}

void ACoinActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnSelect();
}

void ACoinActor::OnSelect()
{
	CoinMesh->SetHiddenInGame(true);
	CoinMesh->SetSimulatePhysics(false);
	CoinMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (SelectedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SelectedSound);
	}

	UFunctionUI::World = GetWorld();
	UFunctionUI::AddMoney(CoinValue);

	if (CoinWidgetClass)
	{
		CoinWidget = CreateWidget<UUserWidget>(GetWorld(), CoinWidgetClass);
		CoinWidget->AddToViewport();
	}
	if (CoinWidget)
	{
		FVector2D ActorScreenPosition;
		if (PlayerController && UGameplayStatics::ProjectWorldToScreen(PlayerController, CoinMesh->GetComponentLocation(), ActorScreenPosition))
		{
			StartPosition = ActorScreenPosition;

			if (MoveCurve)
			{
				FVector2D ScreenSize;
				GEngine->GameViewport->GetViewportSize(ScreenSize);
				EndPosition = FVector2D(50, ScreenSize.Y);

				MoveFunction.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ACoinActor, UpdateCoinPosition));
				SelectTimelineFinishedEvent.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ACoinActor, OnSelectTimelineFinished));
				MoveTimeline.AddInterpFloat(MoveCurve, MoveFunction);
				MoveTimeline.SetTimelineFinishedFunc(SelectTimelineFinishedEvent);
				MoveTimeline.SetLooping(false);
				MoveTimeline.PlayFromStart();
			}
		}
	}
}

