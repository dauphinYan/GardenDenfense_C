#define ECC_PlantArea ECollisionChannel::ECC_GameTraceChannel1

#include "Actor_PlantedArea.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "GardenDefence_C/Enum/OperationState.h"
#include "GardenDefence_C/Plant/Actor_PlacedPlant.h"
#include "GardenDefence_C/Plant/PlacedPlant/Actor_PlacedPlant_SunFlower.h"

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

void AActor_PlantedArea::GrowPlant(EPlacedPlantName InPlacedPlantName)
{
	switch (InPlacedPlantName)
	{
	case EPlacedPlantName::PPN_SunFlower:
		const FString PlantPath = TEXT("Blueprint'/Game/Blueprint/Plant/PlacedPlant/BP_PlacedPlant_SunFlower.BP_PlacedPlant_SunFlower_C'");
		UClass* PlantClass = StaticLoadClass(AActor_PlacedPlant_SunFlower::StaticClass(), nullptr, *PlantPath);

		FVector SpawnLocation = PlayerController->GetCursorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		Plant = GetWorld()->SpawnActor<AActor_PlacedPlant_SunFlower>(PlantClass, SpawnLocation, SpawnRotation);
		if (Plant)
		{
			bIsPlanted = true;
		}
		break;
		//case EPlacedPlantName::PPN_WallNut:
		//	break;
		//case EPlacedPlantName::PPN_Potatomine:
		//	break;
		//case EPlacedPlantName::PPN_CherryBomb:
		//	break;
		//case EPlacedPlantName::PPN_SpikeWeed:
		//	break;
		//case EPlacedPlantName::PPN_TorchStump:
		//	break;
		//case EPlacedPlantName::PPN_DefaultMax:
		//	break;
		//default:
		//	break;
	}
}

void AActor_PlantedArea::RemovePlant()
{
}

