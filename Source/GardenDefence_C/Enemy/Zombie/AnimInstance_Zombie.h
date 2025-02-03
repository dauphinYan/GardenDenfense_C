// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Zombie.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API UAnimInstance_Zombie : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAttacking = false;

	
private:
	class AEnemyCharacter_Zombie* ZombieCharacter;

	class AZombieController* ZombieController;
};
