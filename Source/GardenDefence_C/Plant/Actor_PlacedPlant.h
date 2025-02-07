#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GardenDefence_C/Structure/Structure_PlantInfo.h"
#include "GardenDefence_C/Enum/PlantName.h"
#include "Actor_PlacedPlant.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PlacedPlant : public AActor
{
	GENERATED_BODY()

public:
	AActor_PlacedPlant();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	EPlacedPlantName PlacedPlantName = EPlacedPlantName::PPN_None;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlantStaticMesh;

	float Health = 1;
	float Damage = 1;
	float AtkSpeed = 1;

	UFUNCTION()
	virtual void ReceiveDamage(AActor* DamageActor, float InDamage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	virtual void OnPlantDestroyed();
};
