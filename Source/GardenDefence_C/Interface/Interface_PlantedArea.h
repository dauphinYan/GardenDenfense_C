#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GardenDefence_C/Enum/PlacedPlantName.h"
#include "Interface_PlantedArea.generated.h"

UINTERFACE(MinimalAPI)
class UInterface_PlantedArea : public UInterface
{
	GENERATED_BODY()
};

class GARDENDEFENCE_C_API IInterface_PlantedArea
{
	GENERATED_BODY()

public:
	virtual	bool GrowPlant(EPlacedPlantName InPlacedPlantName);
	virtual bool RemovePlant();
};
