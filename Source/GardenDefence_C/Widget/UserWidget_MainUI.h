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
	UPROPERTY(meta = (BindWidget))
	class UUserWidget_SeedBank* SeedBank;

private:


};
