// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyCharacter.h"
#include "EnemyCharacter_Zombie.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API AEnemyCharacter_Zombie : public AEnemyCharacter
{
	GENERATED_BODY()

protected:
	virtual void ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser) override;
	virtual void AttackTarget() override;
	virtual void OnArmorDestroyed() override;
	virtual void OnEnemyDied() override;

	class AZombieController* ZombieController;
};
