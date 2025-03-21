// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_ShopInGame.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API UUserWidget_ShopInGame : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnViewportAdded();

	UFUNCTION(BlueprintCallable)
	void OnViewportClosed();

	UPROPERTY(BlueprintReadWrite)
	TArray<class UUserWidget_PlantInfoDetail*> PlantInfoPanels;

	UFUNCTION(BlueprintCallable)
	void RefreshBag();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SunValueText;

	UFUNCTION()
	void UpdateSunValue();

protected:
	UFUNCTION(BlueprintCallable)
	void GetNecObject();

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
