#define ECC_PlantArea ECollisionChannel::ECC_GameTraceChannel1

#include "Actor_PlantedArea.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "GardenDefence_C/Enum/OperationState.h"

AActor_PlantedArea::AActor_PlantedArea()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	ArrowWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Arrow"));
	ArrowWidget->SetupAttachment(RootComponent);
	ArrowWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArrowWidget->SetWidgetSpace(EWidgetSpace::World);
	ArrowWidget->SetDrawSize(FVector2D(200.f, 200.f));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Block);

	if (BoxCollision)
	{
		BoxCollision->OnBeginCursorOver.AddDynamic(this, &AActor_PlantedArea::OnCursorEnter);
		BoxCollision->OnEndCursorOver.AddDynamic(this, &AActor_PlantedArea::OnCursorLeave);
	}
}

void AActor_PlantedArea::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
}

void AActor_PlantedArea::OnCursorEnter(UPrimitiveComponent* TouchedComponent)
{
	PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
	if (PlayerController == nullptr) return;
	if (PlayerController->OperationState == EOperationState::EOS_SelectingPlant)
	{
		SetArrowVisibility(true);
	}

}

void AActor_PlantedArea::OnCursorLeave(UPrimitiveComponent* TouchedComponent)
{
	PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
	if (PlayerController == nullptr) return;
	if (PlayerController->OperationState == EOperationState::EOS_SelectingPlant)
	{
		SetArrowVisibility(false);
	}

}

void AActor_PlantedArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActor_PlantedArea::SetArrowVisibility(bool bCanSee)
{
	if (ArrowWidget == nullptr) return;
	ArrowWidget->SetVisibility(bCanSee);
}

