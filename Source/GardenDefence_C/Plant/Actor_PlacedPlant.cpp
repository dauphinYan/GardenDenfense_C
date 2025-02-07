#include "Actor_PlacedPlant.h"
#include "Components/StaticMeshComponent.h"

AActor_PlacedPlant::AActor_PlacedPlant()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	PlantStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plant Mesh"));
	PlantStaticMesh->SetupAttachment(RootComponent);

	OnTakeAnyDamage.AddDynamic(this, &AActor_PlacedPlant::ReceiveDamage);

}

void AActor_PlacedPlant::BeginPlay()
{
	Super::BeginPlay();

	const FString DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_PlacedPlantInfo.DT_PlacedPlantInfo'");
	UDataTable* PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
	if (PlantDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *DataTablePath);
		return;
	}
	TArray<FName> RowNames = PlantDataTable->GetRowNames();
	for (FName RowName : RowNames)
	{
		FPlacedPlantInfo* PlantInfo = PlantDataTable->FindRow<FPlacedPlantInfo>(RowName, TEXT("Plant Info"));
		if (PlantInfo->PlacedPlantName == PlacedPlantName)
		{
			Health = PlantInfo->Health;
			Damage = PlantInfo->Damage;
			AtkSpeed = PlantInfo->AtkSpeed;
		}
		else continue;
	}
}

void AActor_PlacedPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActor_PlacedPlant::ReceiveDamage(AActor* DamageActor, float InDamage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	
}

void AActor_PlacedPlant::OnPlantDestroyed()
{
	
	Destroy();
}

