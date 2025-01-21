// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BulletBase.h"
#include "SnowPea.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API ASnowPea : public ABulletBase
{
	GENERATED_BODY()

public:
	ASnowPea();

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
