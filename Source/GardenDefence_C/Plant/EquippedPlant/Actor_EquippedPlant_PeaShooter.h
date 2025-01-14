
#pragma once

#include "CoreMinimal.h"
#include "../Actor_EquippedPlant.h"
#include "Actor_EquippedPlant_PeaShooter.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API AActor_EquippedPlant_PeaShooter : public AActor_EquippedPlant
{
	GENERATED_BODY()

public:
	AActor_EquippedPlant_PeaShooter();

protected:
	virtual void BeginPlay() override;

	virtual void SearchEnemy() override;
	virtual void AttackEnemy() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBulletPool* BulletPool;
};
