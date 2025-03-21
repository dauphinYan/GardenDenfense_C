#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GardenDefence_C/Structure/Structure_PlantInfo.h"
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

	UPROPERTY()
	class UUserWidget_Shovel* W_Shovel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> W_ShovelClass;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Shovel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SunValueText;

	void UpdatePlantBox();
	void SelectPlantCard(int32 Index);
	void OnCanceledSelectPlantCard();
	void OnSelectedShovel();
	void OnCanceledShovel();

	UFUNCTION()
	void UpdateSunValue();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget_SeedBankOneCard> SeedBankOneCardClass;

	UPROPERTY()
	TArray<UUserWidget_SeedBankOneCard*> SeedBankCards;

	int32 CurIndex = -1;

	UPROPERTY()
	class AMainPlayerController* PlayerController;

	UPROPERTY(EditDefaultsOnly)
	class USoundWave* SelectSoundWave;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* PauseSoundWave;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* GrowSoundWave;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AMainGameStateBase* GameState;
};
