// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GardenDefence_C/Structure/Structure_ZombieInfo.h"
#include "GardenDefence_C/Interface/Interface_Enemy.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AEnemyCharacter : public ACharacter, public IInterface_Enemy
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	virtual bool IsAlive() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool bIsAlive;
};
