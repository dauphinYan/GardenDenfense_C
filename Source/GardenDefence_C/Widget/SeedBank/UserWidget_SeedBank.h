#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GardenDefence_C/Structure/Structure_PlacedPlantInfo.h"
#include "UserWidget_SeedBank.generated.h"

UCLASS()
class GARDENDEFENCE_C_API UUserWidget_SeedBank : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdatePlantBox();

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* PlantBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget_SeedBankOneCard> SeedBankOneCardClass;

private:

};
