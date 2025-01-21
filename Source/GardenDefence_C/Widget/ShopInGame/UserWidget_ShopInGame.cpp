#include "UserWidget_ShopInGame.h"
#include "GardenDefence_C/Character/MainCharacter.h"
#include "GardenDefence_C/Character/CombatComponent.h"
#include "GardenDefence_C/GamePlay/MainGameStateBase.h"
#include "Components/Button.h"
#include "GardenDefence_C/Structure/Structure_PlantInfo.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UserWidget_PlantInfoDetail.h"

void UUserWidget_ShopInGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_EquippedPlantInfo.DT_EquippedPlantInfo'");
	PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
}

void UUserWidget_ShopInGame::NativeConstruct()
{
	Super::NativeConstruct();

	GetNecObject();
}



void UUserWidget_ShopInGame::GetNecObject()
{
	Character = Character == nullptr ? Character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : Character;
	CombatComponent = CombatComponent == nullptr ? CombatComponent = Character->GetCombatComponent() : CombatComponent;
	GameState = GameState == nullptr ? GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;
}

void UUserWidget_ShopInGame::RefreshBag()
{
	for (UUserWidget_PlantInfoDetail* PlantInfoPanel : PlantInfoPanels)
	{
		PlantInfoPanel->UpdateInfo();
	}
}

void UUserWidget_ShopInGame::UpdateSunValue()
{
	GameState = GameState == nullptr ? GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;
	int32 SunValueInteger = FMath::FloorToInt(GameState->GetSunValue());
	FString SunValueString = FString::FromInt(SunValueInteger);
	SunValueText->SetText(FText::FromString(SunValueString));
}

void UUserWidget_ShopInGame::OnViewportAdded()
{
	UpdateSunValue();
}

void UUserWidget_ShopInGame::OnViewportClosed()
{
	CombatComponent->UpdateEquippedPlant();
	for (auto Panel : PlantInfoPanels)
	{
		if (Panel->EnhanceButton)
		{
			Panel->EnhanceButton->OnClicked.RemoveDynamic(Panel, &UUserWidget_PlantInfoDetail::EnhancedPlant);
		}
	}
}
