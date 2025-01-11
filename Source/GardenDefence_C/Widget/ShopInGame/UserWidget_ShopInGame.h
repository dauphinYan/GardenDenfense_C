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
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void GetNecObject();

	//UPROPERTY(meta = (BindWidget))
	//class UButton* Button_Quit;

private:
	UPROPERTY()
	class AMainCharacter* Character;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatComponent;
};
