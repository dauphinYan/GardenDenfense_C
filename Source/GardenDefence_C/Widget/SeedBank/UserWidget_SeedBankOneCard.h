#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GardenDefence_C/Structure/Structure_PlacedPlantInfo.h"
#include "UserWidget_SeedBankOneCard.generated.h"

UCLASS()
class GARDENDEFENCE_C_API UUserWidget_SeedBankOneCard : public UUserWidget
{
	GENERATED_BODY()

private:

public:
	void SetCardInfo(FPlacedPlantInfo InPlacedPlantInfo);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SunText;

	UPROPERTY(meta = (BindWidget))
	class UImage* PlantImage;
};
