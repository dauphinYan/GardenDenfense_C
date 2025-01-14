#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GardenDefence_C/Structure/Structure_PlantInfo.h"
#include "GardenDefence_C/Enum/PlantName.h"
#include "GardenDefence_C/Enemy/EnemyCharacter.h"
#include "Actor_EquippedPlant.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_EquippedPlant : public AActor
{
	GENERATED_BODY()

public:
	AActor_EquippedPlant();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SearchEnemy();
	virtual void AttackEnemy();

	UPROPERTY(EditDefaultsOnly)
	EEquippedPlantName EquippedPlantName;

	float Damage = 1;
	float AtkSpeed = 1;
	float Level = 1;
	float AtkRange = 1;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlantStaticMesh;

	UPROPERTY()
	AActor* TargetEnemy;

	FTimerHandle SearchEnemyHandle;
	FTimerHandle AttackEnemyHandle;

public:
	void SetLevel(int32 NewLevel);
};
