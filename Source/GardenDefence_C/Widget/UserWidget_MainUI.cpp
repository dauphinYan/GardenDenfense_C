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
			// 商店界面已经在视图中，关闭它
			Shop->RemoveFromParent();
			Shop->OnViewportClosed(); // 调用自定义关闭事件
		}
		else
		{
			// 商店界面不在视图中，打开它
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
