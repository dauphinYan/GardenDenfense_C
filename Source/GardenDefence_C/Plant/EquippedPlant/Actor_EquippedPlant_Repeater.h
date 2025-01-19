#pragma once

#include "CoreMinimal.h"
#include "../Actor_EquippedPlant.h"
#include "Actor_EquippedPlant_Repeater.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API AActor_EquippedPlant_Repeater : public AActor_EquippedPlant
{
	GENERATED_BODY()

public:
	AActor_EquippedPlant_Repeater();

protected:
	virtual void BeginPlay() override;
	virtual void AttackEnemy() override;

	void FireBullet();

private:
	UPROPERTY(EditDefaultsOnly)
	class UBulletPool* BulletPool;

	int32 NumShots = 2;
	int32 ShotsRemaining = NumShots;
	FTimerHandle ShootHandle;
};
