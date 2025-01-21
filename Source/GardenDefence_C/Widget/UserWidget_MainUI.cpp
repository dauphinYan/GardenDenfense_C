#include "UserWidget_MainUI.h"
#include "ShopInGame/UserWidget_ShopInGame.h"
#include "SeedBank/UserWidget_SeedBank.h"

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
	if (Shop)
	{
		if (Shop->IsInViewport())
		{
			Shop->OnViewportClosed();
			Shop->RemoveFromParent();
		}
		else
		{
			Shop->AddToViewport();
			Shop->OnViewportAdded();
		}
	}
}

void UUserWidget_MainUI::RefreshShopBag()
{
	Shop->RefreshBag();
}

void UUserWidget_MainUI::UpdateSun()
{
	if (Shop)
		Shop->UpdateSunValue();
	if (SeedBank)
		SeedBank->UpdateSunValue();
}
