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

public:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* PlantBox;

	void UpdatePlantBox();
	void SelectPlantCard(int32 Index);


private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget_SeedBankOneCard> SeedBankOneCardClass;

	TArray<UUserWidget_SeedBankOneCard*> SeedBankCards;

	int32 CurIndex = -1;

	class AMainPlayerController* PlayerController;

};
