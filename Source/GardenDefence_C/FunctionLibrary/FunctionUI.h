// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionUI.generated.h"

UCLASS()
class GARDENDEFENCE_C_API UFunctionUI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static int32 GetMoneyAmount();

	UFUNCTION(BlueprintCallable)
	static void AddMoney(int32 InValue);

	static UWorld* World;

private:
	static TWeakObjectPtr<class UMainGameInstance> CachedGameInstance;

	static UMainGameInstance* GetGameInstance1();
};
