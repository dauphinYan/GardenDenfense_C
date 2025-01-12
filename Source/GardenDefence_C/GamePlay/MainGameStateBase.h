// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GARDENDEFENCE_C_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	float SunValue = 100;

public:
	UFUNCTION(BlueprintCallable)
	float GetSunValue() { return SunValue; }

	UFUNCTION(BlueprintCallable)
	void AddSunValue(float AddValue);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AGamePlayHUD* CharacterHUD;
};
