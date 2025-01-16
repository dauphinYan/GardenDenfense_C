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


	const FString DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_EquippedPlantInfo.DT_EquippedPlantInfo'");
	UDataTable* PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
	if (PlantDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *DataTablePath);
		return;
	}
	TArray<FName> RowNames = PlantDataTable->GetRowNames();
	for (FName RowName : RowNames)
	{
		FEquippedPlantInfo* PlantInfo = PlantDataTable->FindRow<FEquippedPlantInfo>(RowName, TEXT("Plant Info"));
		if (PlantInfo->eEquippedPlantName == EquippedPlantName)
		{
			Damage = PlantInfo->Damage;
			AtkSpeed = PlantInfo->AtkSpeed;
			AtkRange = PlantInfo->AtkRange;
		}
		else continue;
	}
	GetWorld()->GetTimerManager().SetTimer(SearchEnemyHandle, this, &AActor_EquippedPlant::SearchEnemy, 0.5f, true);
	GetWorld()->GetTimerManager().SetTimer(AttackEnemyHandle, this, &AActor_EquippedPlant::AttackEnemy, AtkSpeed, true);
}

void AActor_EquippedPlant::SearchEnemy()
{
	FVector Location = GetActorLocation();
	TArray<FOverlapResult> OverlapResults;

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(AtkRange);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bool bHasHit = GetWorld()->OverlapMultiByObjectType(OverlapResults, Location, FQuat::Identity, ECC_Enemy, CollisionShape, CollisionQueryParams);

	if (bHasHit)
	{
		float ClosestDistance = FLT_MAX;
		AActor* ClosestEnemy = nullptr;
		for (const FOverlapResult& Result : OverlapResults)
		{
			AActor* Enemy = Result.GetActor();
			float Distance = (Enemy->GetActorLocation() - Location).Size();
			if (ClosestDistance > Distance)
			{
				ClosestDistance = Distance;
				ClosestEnemy = Enemy;
			}
		}
		TargetEnemy = ClosestEnemy;
	}
	else
		TargetEnemy = nullptr;

	if (TargetEnemy)
		DrawDebugSphere(GetWorld(), TargetEnemy->GetActorLocation(), 50.f, 24, FColor::Red, false, 1.0f);
}

void AActor_EquippedPlant::AttackEnemy()
{
}

void AActor_EquippedPlant::SetLevel(int32 NewLevel)
{
	Level = NewLevel;
}

void AActor_EquippedPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

