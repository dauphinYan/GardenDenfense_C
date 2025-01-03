// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_PlacedPlant.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PlacedPlant : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor_PlacedPlant();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlantStaticMesh;

};
