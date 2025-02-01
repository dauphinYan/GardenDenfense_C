#include "MainGameInstance.h"
#include "GardenDefence_C/Widget/Component/WalletWidget.h"

void UMainGameInstance::UpdateMoneyAmount(int32 InValue)
{
	if (WalletWidget == nullptr)
	{
		if (WalletWidgetClass)
		{
			WalletWidget = CreateWidget<UWalletWidget>(GetWorld(), WalletWidgetClass);
			WalletWidget->AddToViewport();
		}
	}

	if (MoneyAmount + InValue >= 0)
	{
		MoneyAmount += InValue;
		if (WalletWidget == nullptr) return;
		WalletWidget->OnWalletChanged();
	}
}
