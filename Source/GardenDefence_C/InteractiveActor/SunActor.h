// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SunActor.generated.h"

UCLASS()
class GARDENDEFENCE_C_API ASunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASunActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SunMesh;
};
