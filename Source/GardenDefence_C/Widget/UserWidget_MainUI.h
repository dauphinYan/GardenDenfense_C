// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_MainUI.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API UUserWidget_MainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UUserWidget_SeedBank* SeedBank;

	void SetShopVisibility();
	void RefreshShopBag();
	void UpdateSun();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget_ShopInGame> ShopClass;

	UPROPERTY()
	UUserWidget_ShopInGame* Shop;


};
