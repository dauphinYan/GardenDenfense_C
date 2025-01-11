#include "UserWidget_MainUI.h"
#include "ShopInGame/UserWidget_ShopInGame.h"

void UUserWidget_MainUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (ShopClass && Shop == nullptr)
	{
		Shop = CreateWidget<UUserWidget_ShopInGame>(GetWorld()->GetFirstPlayerController(), ShopClass);
	}
}

void UUserWidget_MainUI::SetShopVisibility()
{
	if (Shop == nullptr && ShopClass)
	{
		Shop = CreateWidget<UUserWidget_ShopInGame>(GetWorld()->GetFirstPlayerController(), ShopClass);
	}
	if (Shop)
	{
		if (Shop->IsInViewport())
		{
			// is in View.
			Shop->RemoveFromParent();
		}
		else
		{
			// is not in View.
			Shop->AddToViewport();
		}
	}

}
