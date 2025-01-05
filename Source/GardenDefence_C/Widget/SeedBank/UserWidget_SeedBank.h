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
	void OnCanceledSelect();


private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget_SeedBankOneCard> SeedBankOneCardClass;

	UPROPERTY()
	TArray<UUserWidget_SeedBankOneCard*> SeedBankCards;

	int32 CurIndex = -1;

	UPROPERTY()
	class AMainPlayerController* PlayerController;

	UPROPERTY()
	class USoundWave* SelectSoundWave;

	UPROPERTY()
	class USoundWave* GrowSoundWave;

};
