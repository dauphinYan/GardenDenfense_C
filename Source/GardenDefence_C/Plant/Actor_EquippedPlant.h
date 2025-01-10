// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_EquippedPlant.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_EquippedPlant : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor_EquippedPlant();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlantStaticMesh;

};
