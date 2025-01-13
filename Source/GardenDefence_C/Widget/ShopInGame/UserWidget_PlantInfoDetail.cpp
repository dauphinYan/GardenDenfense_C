// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_PlantInfoDetail.h"
#include "GardenDefence_C/Structure/Structure_EquippedPlantInfo.h"
#include "GardenDefence_C/Character/MainCharacter.h"
#include "GardenDefence_C/Character/CombatComponent.h"
#include "GardenDefence_C/GamePlay/MainGameStateBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUserWidget_PlantInfoDetail::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Character == nullptr ? Character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : Character;
	CombatComponent = CombatComponent == nullptr ? CombatComponent = Character->GetCombatComponent() : CombatComponent;
	GameState = GameState == nullptr ? GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;

	DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_EquippedPlantInfo.DT_EquippedPlantInfo'");
	PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
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
		if (Item->eEquippedPlantName != CombatComponent->OwningEquippedPlantNames[Index]) continue;
		else
		{
			MainPlantText->SetText(Item->PlantName);
			PlantText->SetText(Item->PlantName);
			MainPlantImage->SetBrushResourceObject(Item->PlantImage);
			PlantImage->SetBrushResourceObject(Item->PlantImage);
		}
	}
}

