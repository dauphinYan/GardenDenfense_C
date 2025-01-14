// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_PlantInfoDetail.h"

#include "GardenDefence_C/Character/MainCharacter.h"
#include "GardenDefence_C/Character/CombatComponent.h"
#include "GardenDefence_C/GamePlay/MainGameStateBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UUserWidget_PlantInfoDetail::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Character == nullptr ? Character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : Character;
	CombatComponent = CombatComponent == nullptr ? CombatComponent = Character->GetCombatComponent() : CombatComponent;
	GameState = GameState == nullptr ? GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;

	DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_EquippedPlantInfo.DT_EquippedPlantInfo'");
	PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);

	if (EnhanceButton)
	{
		EnhanceButton->OnClicked.AddDynamic(this, &UUserWidget_PlantInfoDetail::EnhancedPlant);
	}
}

void UUserWidget_PlantInfoDetail::UpdateInfo()
{
	if (PlantDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *DataTablePath);
		return;
	}

	TArray<FName> RowNames = PlantDataTable->GetRowNames();
	for (FName RowName : RowNames)
	{
		FEquippedPlantInfo* Item = PlantDataTable->FindRow<FEquippedPlantInfo>(RowName, TEXT("Plant Info"));
		Character = Character == nullptr ? Character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : Character;
		CombatComponent = CombatComponent == nullptr ? CombatComponent = Character->GetCombatComponent() : CombatComponent;
		if (Item->eEquippedPlantName != CombatComponent->OwningEquippedPlants[Index].PlantName) continue;
		else
		{
			CurPlantItem = *Item;
			MainPlantText->SetText(CurPlantItem.PlantName);
			PlantText->SetText(CurPlantItem.PlantName);
			MainPlantImage->SetBrushResourceObject(CurPlantItem.PlantImage);
			PlantImage->SetBrushResourceObject(CurPlantItem.PlantImage);
			LevelText->SetText(FText::AsNumber(CombatComponent->OwningEquippedPlants[Index].PlantLevel));
			FText InputText;
			for (int i = 0; i < CombatComponent->OwningEquippedPlants[Index].PlantLevel; i++)
			{
				if (i < CurPlantItem.SkillTree.Description.Num())
				{
					if (InputText.IsEmpty())
					{
						InputText = CurPlantItem.SkillTree.Description[i];
					}
					else
					{
						InputText = FText::Join(FText::FromString(TEXT("\n")), InputText, CurPlantItem.SkillTree.Description[i]);
					}
				}
			}
			CurEffectText->SetText(InputText);
		}
	}
}

void UUserWidget_PlantInfoDetail::EnhancedPlant()
{
	CombatComponent = CombatComponent == nullptr ? CombatComponent = Character->GetCombatComponent() : CombatComponent;
	if (CombatComponent->OwningEquippedPlants[Index].PlantLevel < CurPlantItem.SkillTree.Level)
	{
		if (CombatComponent->EnhanceOwningEquippedPlant(Index))
		{
			// success

		}
		else
		{
			// error

		}
	}
}