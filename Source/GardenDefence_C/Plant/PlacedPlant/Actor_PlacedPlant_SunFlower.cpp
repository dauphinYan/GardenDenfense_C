#include "Actor_PlacedPlant_SunFlower.h"



AActor_PlacedPlant_SunFlower::AActor_PlacedPlant_SunFlower()
{
	PlacedPlantName = EPlacedPlantName::PPN_SunFlower;
}

void AActor_PlacedPlant_SunFlower::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ProduceHandle, this, &AActor_PlacedPlant_SunFlower::ProduceSunlight, 15.f, true);
}

void AActor_PlacedPlant_SunFlower::ReceiveDamage(AActor* DamageActor, float InDamage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	if (Health-InDamage > 0)
	{
		Health -= InDamage;
	}
	else
	{
		OnPlantDestroyed();
	}
}

void AActor_PlacedPlant_SunFlower::ProduceSunlight()
{
	if (SunClass == nullptr) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 100.f);
	FRotator SpawnRotation(0.f, 0.f, 0.f);
	ASunActor* SpawnedSun = GetWorld()->SpawnActor<ASunActor>(SunClass, SpawnLocation, SpawnRotation);
	if (SpawnedSun)
	{
		UStaticMeshComponent* Mesh = SpawnedSun->SunMesh;

		FVector RandomForce = FVector(FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(300.0f, 500.0f));
		Mesh->AddImpulse(RandomForce, NAME_None, true);
	}
}
