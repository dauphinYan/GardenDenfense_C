#include "WalletWidget.h"
#include "Components/TextBlock.h"
#include "GardenDefence_C/FunctionLibrary/FunctionUI.h"

void UWalletWidget::OnWalletChanged()
{

	MoneyText->SetText(FText::AsNumber(UFunctionUI::GetMoneyAmount()));
	PlayAnimation(MoneyAddAnimation);
}
