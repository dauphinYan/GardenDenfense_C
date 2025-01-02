#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_PlantedArea.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PlantedArea : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor_PlantedArea();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
