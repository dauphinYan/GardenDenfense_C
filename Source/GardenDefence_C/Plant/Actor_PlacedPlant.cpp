#include "Actor_PlacedPlant.h"
#include "Components/StaticMeshComponent.h"

AActor_PlacedPlant::AActor_PlacedPlant()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	PlantStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plant Mesh"));
	PlantStaticMesh->SetupAttachment(RootComponent);
}

void AActor_PlacedPlant::BeginPlay()
{
	Super::BeginPlay();

}

void AActor_PlacedPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

