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
	if (Shop == nullptr && ShopClass)
	{
		Shop = CreateWidget<UUserWidget_ShopInGame>(GetWorld()->GetFirstPlayerController(), ShopClass);
	}

	if (Shop && IsValid(Shop))
	{
		if (Shop->IsInViewport())
		{
			Shop->RemoveFromParent();
			Shop->OnViewportClosed();
		}
		else
		{
			Shop->AddToViewport();
		}
	}
	else
	{
		Shop = CreateWidget<UUserWidget_ShopInGame>(GetWorld()->GetFirstPlayerController(), ShopClass);
	}

}

void UUserWidget_MainUI::RefreshShopBag()
{
	Shop->RefreshBag();
}

void UUserWidget_MainUI::UpdateSun()
{
	Shop->UpdateSunValue();
	SeedBank->UpdateSunValue();
}
