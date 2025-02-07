// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actor_PlacedPlant.h"
#include "Wallnut.generated.h"

/**
 * 
 */
UCLASS()
class GARDENDEFENCE_C_API AWallnut : public AActor_PlacedPlant
{
	GENERATED_BODY()
	
public:
	AWallnut();

	virtual void ReceiveDamage(AActor* DamageActor, float InDamage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser) override;
};
