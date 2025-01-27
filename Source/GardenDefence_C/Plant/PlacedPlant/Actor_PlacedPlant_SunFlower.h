#pragma once

#include "CoreMinimal.h"
#include "../Actor_PlacedPlant.h"
#include "GardenDefence_C/InteractiveActor/SunActor.h"
#include "Actor_PlacedPlant_SunFlower.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PlacedPlant_SunFlower : public AActor_PlacedPlant
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	void ProduceSunlight();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASunActor> SunClass;

	FTimerHandle ProduceHandle;
};
