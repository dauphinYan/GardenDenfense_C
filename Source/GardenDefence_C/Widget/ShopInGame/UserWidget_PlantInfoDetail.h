// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_PlantInfoDetail.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API UUserWidget_PlantInfoDetail : public UUserWidget
{
	GENERATED_BODY()



public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite)
	int32 Index;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MainPlantText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlantText;

	UPROPERTY(meta = (BindWidget))
	class UImage* MainPlantImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* PlantImage;

	UFUNCTION(BlueprintCallable)
	void UpdateInfo();

private:
	UPROPERTY()
	class AMainCharacter* Character;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatComponent;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AMainGameStateBase* GameState;



	FString DataTablePath;
	UPROPERTY();
	UDataTable* PlantDataTable;
};
