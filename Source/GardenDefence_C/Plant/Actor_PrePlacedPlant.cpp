#include "Actor_PrePlacedPlant.h"
#include "Components/StaticMeshComponent.h"

AActor_PrePlacedPlant::AActor_PrePlacedPlant()
{
	PrimaryActorTick.bCanEverTick = false;

	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plant Mesh"));
	PlantMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AActor_PrePlacedPlant::BeginPlay()
{
	Super::BeginPlay();

}

void AActor_PrePlacedPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

