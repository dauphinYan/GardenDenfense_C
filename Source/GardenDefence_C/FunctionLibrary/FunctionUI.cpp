#include "FunctionUI.h"
#include "Kismet/GameplayStatics.h"
#include "GardenDefence_C/GamePlay/MainGameInstance.h"

TWeakObjectPtr<UMainGameInstance> UFunctionUI::CachedGameInstance = nullptr;
UWorld* UFunctionUI::World = nullptr;

UMainGameInstance* UFunctionUI::GetGameInstance1()
{
	if (CachedGameInstance.IsValid())
	{
		return CachedGameInstance.Get();
	}


	UMainGameInstance* GameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(World));
	if (GameInstance)
	{
		CachedGameInstance = GameInstance;
	}
	return GameInstance;
}

int32 UFunctionUI::GetMoneyAmount()
{
	UMainGameInstance* GameInstance = GetGameInstance1();
	if (GameInstance)
	{
		return GameInstance->GetMoneyAmount();
	}
	return 0;
}

void UFunctionUI::AddMoney(int32 InValue)
{
	UMainGameInstance* GameInstance = GetGameInstance1();
	if (GameInstance)
	{
		GameInstance->UpdateMoneyAmount(InValue);
	}
}