#include "Actor_PrePlacedPlant.h"
#include "GardenDefence_C/Structure/Structure_PlacedPlantInfo.h"
#include "Components/StaticMeshComponent.h"

AActor_PrePlacedPlant::AActor_PrePlacedPlant()
{
	PrimaryActorTick.bCanEverTick = false;

	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plant Mesh"));
	RootComponent = PlantMesh;
	PlantMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlantMesh->SetCastShadow(false);

	//初始化植物信息
	const FString PlantDataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_PlacedPlantInfo.DT_PlacedPlantInfo'");
	UDataTable* PlantDataTable = LoadObject<UDataTable>(nullptr, *PlantDataTablePath);
	if (PlantDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *PlantDataTablePath);
		return;
	}
	TArray<FName> RowNames = PlantDataTable->GetRowNames();
	for (FName RowName : RowNames)
	{
		FPlacedPlantInfo* RowData = PlantDataTable->FindRow<FPlacedPlantInfo>(RowName, TEXT("Plant Info"));
		if (!RowData->MeshPath.IsEmpty())
		{
			UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, *RowData->MeshPath);
			if (LoadedMesh)
			{
				PlantMeshMap.Add(RowData->PlacedPlantName, LoadedMesh);
			}
		}
	}
}

void AActor_PrePlacedPlant::BeginPlay()
{
	Super::BeginPlay();

	PlantMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void AActor_PrePlacedPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActor_PrePlacedPlant::SetPlacedPlant(EPlacedPlantName InPlantName)
{
	PlacedPlantName = InPlantName;
	if (PlantMesh == nullptr)
		return;
	if (PlantMeshMap.Contains(PlacedPlantName))
	{
		PlantMesh->SetStaticMesh(PlantMeshMap[PlacedPlantName]);
		PlantMesh->SetVisibility(true);
	}
	else
	{
		PlantMesh->SetStaticMesh(nullptr);
		PlantMesh->SetVisibility(false);
	}
}

