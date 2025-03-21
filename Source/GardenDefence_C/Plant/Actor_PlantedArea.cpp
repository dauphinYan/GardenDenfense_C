#define ECC_PlantArea ECollisionChannel::ECC_GameTraceChannel1

#include "Actor_PlantedArea.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "GardenDefence_C/Enum/OperationState.h"
#include "GardenDefence_C/Structure/Structure_PlantInfo.h"
#include "GardenDefence_C/Plant/Actor_PlacedPlant.h"
#include "GardenDefence_C/GamePlay/MainGameStateBase.h"
#include "GardenDefence_C/Plant/PlacedPlant/Actor_PlacedPlant_SunFlower.h"
#include "GardenDefence_C/Plant/PlacedPlant/Wallnut.h"

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
	if (PlayerController->OperationState == EOperationState::EOS_SelectingPlant || PlayerController->OperationState == EOperationState::EOS_Shovel)
	{
		SetArrowVisibility(true);
	}

}

void AActor_PlantedArea::OnCursorLeave(UPrimitiveComponent* TouchedComponent)
{
	SetArrowVisibility(false);
	PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
	if (PlayerController == nullptr) return;
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

bool AActor_PlantedArea::GrowPlant(EPlacedPlantName InPlacedPlantName)
{
	if (bIsPlanted == true) return false;
	switch (InPlacedPlantName)
	{
	case EPlacedPlantName::PPN_SunFlower:
	{
		const FString PlantPath = TEXT("Blueprint'/Game/Blueprint/Plant/PlacedPlant/BP_PlacedPlant_SunFlower.BP_PlacedPlant_SunFlower_C'");
		UClass* PlantClass = StaticLoadClass(AActor_PlacedPlant_SunFlower::StaticClass(), nullptr, *PlantPath);
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation(0.f, 90.f, 0.f);
		Plant = GetWorld()->SpawnActor<AActor_PlacedPlant_SunFlower>(PlantClass, SpawnLocation, SpawnRotation);
		if (Plant)
		{
			bIsPlanted = true;
			SetArrowVisibility(false);
			GetSelectedPlantInfo(InPlacedPlantName);
			Plant->OnDestroyed.AddDynamic(this, &AActor_PlantedArea::OnPlantDestroyed);
			return true;
		}
	}
	break;
	case EPlacedPlantName::PPN_WallNut:
	{
		const FString PlantPath = TEXT("Blueprint'/Game/Blueprint/Plant/PlacedPlant/BP_Wallnut.BP_Wallnut_C'");
		UClass* PlantClass = StaticLoadClass(AWallnut::StaticClass(), nullptr, *PlantPath);
		FVector SpawnLocation = GetActorLocation();
		//FRotator SpawnRotation(0.f, 90.f, 0.f);
		Plant = GetWorld()->SpawnActor<AWallnut>(PlantClass, SpawnLocation, FRotator::ZeroRotator);
		if (Plant)
		{
			bIsPlanted = true;
			SetArrowVisibility(false);
			GetSelectedPlantInfo(InPlacedPlantName);
			Plant->OnDestroyed.AddDynamic(this, &AActor_PlantedArea::OnPlantDestroyed);
			return true;
		}
	}
	break;
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
	return false;
}

void AActor_PlantedArea::GetSelectedPlantInfo(EPlacedPlantName InPlacedPlantName)
{
	const FString DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_PlacedPlantInfo.DT_PlacedPlantInfo'");
	UDataTable* PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
	if (PlantDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *DataTablePath);
	}
	else
	{
		TArray<FName> RowNames = PlantDataTable->GetRowNames();
		for (int32 i = 0; i < RowNames.Num(); i++)
		{
			FPlacedPlantInfo* RowData = PlantDataTable->FindRow<FPlacedPlantInfo>(RowNames[i], TEXT("Plant Info"));
			if (RowData && RowData->PlacedPlantName == InPlacedPlantName)
			{
				GameState = GameState == nullptr ? GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;
				GameState->AddSunValue(-RowData->Sun);
				break;
			}
		}
	}
}

bool AActor_PlantedArea::RemovePlant()
{
	if (Plant)
	{
		if (Plant->IsValidLowLevel())
			Plant->Destroy();
		return true;
	}
	else
	{
		return false;
	}
}

void AActor_PlantedArea::OnPlantDestroyed(AActor* InPlant)
{
	if (InPlant)
	{
		Plant->OnDestroyed.RemoveDynamic(this, &AActor_PlantedArea::OnPlantDestroyed);
		SetArrowVisibility(false);
		Plant = nullptr;
		bIsPlanted = false;
	}
}
