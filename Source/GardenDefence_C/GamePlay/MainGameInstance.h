#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 *
 */
UCLASS()
class GARDENDEFENCE_C_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void UpdateMoneyAmount(int32 InValue);

private:
	int32 MoneyAmount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "WalletUI")
	TSubclassOf<class UWalletWidget> WalletWidgetClass;

	UWalletWidget* WalletWidget;

public:
	FORCEINLINE int32 GetMoneyAmount() { return MoneyAmount; }
};
