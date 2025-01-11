#include "UserWidget_ShopInGame.h"
#include "GardenDefence_C/Character/MainCharacter.h"
#include "GardenDefence_C/Character/CombatComponent.h"
#include "Components/Button.h"
#include "GardenDefence_C//Structure/Structure_EquippedPlantInfo.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUserWidget_ShopInGame::NativeConstruct()
{
	Super::NativeConstruct();

	GetNecObject();

	DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_EquippedPlantInfo.DT_EquippedPlantInfo'");
	PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
}

void UUserWidget_ShopInGame::GetNecObject()
{
	Character = Character == nullptr ? Character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : Character;
	CombatComponent = CombatComponent == nullptr ? CombatComponent = Character->GetCombatComponent() : CombatComponent;
}

void UUserWidget_ShopInGame::RefreshBag()
{
	for (int32 i = 0; i < 6; i++)
	{
		if (PlantDataTable == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *DataTablePath);
			return;
		}

		if (CombatComponent->OwningEquippedPlantNames.Num() <= i)
		{
			if (FEquippedPlantInfo* Item = PlantDataTable->FindRow<FEquippedPlantInfo>(TEXT("NoPlant"), TEXT("Plant Info")))
			{
				PlantTexts[i]->SetText(FText::FromString(TEXT(" ")));
				PlantImages[i]->SetBrushResourceObject(Item->PlantImage);
			}
			break;
		}

		TArray<FName> RowNames = PlantDataTable->GetRowNames();
		for (FName RowName : RowNames)
		{
			FEquippedPlantInfo* Item = PlantDataTable->FindRow<FEquippedPlantInfo>(RowName, TEXT("Plant Info"));

			if (Item->eEquippedPlantName != CombatComponent->OwningEquippedPlantNames[i]) continue;
			else
			{
				PlantTexts[i]->SetText(Item->PlantName);
				PlantImages[i]->SetBrushResourceObject(Item->PlantImage);
			}
		}
	}
}

void UUserWidget_ShopInGame::OnViewportClosed()
{
	CombatComponent->UpdateEquippedPlant();
}
