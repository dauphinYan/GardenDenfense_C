#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WalletWidget.generated.h"

UCLASS()
class GARDENDEFENCE_C_API UWalletWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void OnWalletChanged();

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* MoneyAddAnimation;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MoneyText;
};
