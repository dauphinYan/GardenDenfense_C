#include "Actor_EquippedPlant.h"

AActor_EquippedPlant::AActor_EquippedPlant()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	PlantStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plant Mesh"));
	PlantStaticMesh->SetupAttachment(RootComponent);
	PlantStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AActor_EquippedPlant::BeginPlay()
{
	Super::BeginPlay();

}

void AActor_EquippedPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

