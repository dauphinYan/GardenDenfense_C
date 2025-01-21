// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actor_EquippedPlant.h"
#include "Actor_SnowPeaShooter.generated.h"

/**
 * 
 */
UCLASS()
class GARDENDEFENCE_C_API AActor_SnowPeaShooter : public AActor_EquippedPlant
{
	GENERATED_BODY()
	
public:
	AActor_SnowPeaShooter();

protected:
	virtual void BeginPlay() override;
	virtual void AttackEnemy() override;

	void FireBullet();

private:
	UPROPERTY(EditDefaultsOnly)
	class UBulletPool* BulletPool;

	int32 NumShots = 1;
	int32 ShotsRemaining = NumShots;
	FTimerHandle ShootHandle;
};
