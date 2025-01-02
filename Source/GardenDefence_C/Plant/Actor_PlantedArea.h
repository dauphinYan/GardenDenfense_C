#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/Interface_PlantedArea.h"
#include "Actor_PlantedArea.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PlantedArea : public AActor, public IInterface_PlantedArea
{
	GENERATED_BODY()

public:
	AActor_PlantedArea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateArrowVisibility() override;
	virtual void RemovePlant() override;

};
