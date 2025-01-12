#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GardenDefence_C/Structure/Structure_PlacedPlantInfo.h"
#include "UserWidget_SeedBankOneCard.generated.h"

UCLASS()
class GARDENDEFENCE_C_API UUserWidget_SeedBankOneCard : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetCardInfo(FPlacedPlantInfo InPlacedPlantInfo, int32 InIndex);

	UFUNCTION(BlueprintCallable)
	void OnSelected();

	UFUNCTION(BlueprintCallable)
	void BeginCool();

	UFUNCTION(BlueprintCallable)
	void OnCanceled();

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SunText;

	UPROPERTY(meta = (BindWidget))
	class UImage* PlantImage;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonChoose;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* CoolingAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OnSelectedAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OnCanceledAnimation;



	UFUNCTION()
	void OnButtonChooseClicked();

private:
	class AMainPlayerController* PlayerController;
	FPlacedPlantInfo PlacedPlantInfo;
	int32 Index = -1;
	bool bIsCool = false;


public:
	FORCEINLINE EPlacedPlantName GetPlantName() { return PlacedPlantInfo.PlacedPlantName; }
	FORCEINLINE float GetSunValue() { return PlacedPlantInfo.Sun; }
};
