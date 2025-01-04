#include "UserWidget_SeedBank.h"
#include "UserWidget_SeedBankOneCard.h"
#include "Components/HorizontalBox.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "GardenDefence_C/Enum/OperationState.h"


void UUserWidget_SeedBank::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	UpdatePlantBox();
}

void UUserWidget_SeedBank::UpdatePlantBox()
{
	if (!SeedBankOneCardClass)
		return;
	PlantBox->ClearChildren();
	SeedBankCards.Empty();
	const FString DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_PlacedPlantInfo.DT_PlacedPlantInfo'");
	UDataTable* PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
	if (PlantDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *DataTablePath);
		return;
	}
	TArray<FName> RowNames = PlantDataTable->GetRowNames();
	for (int32 i = 0; i < RowNames.Num(); i++)
	{
		FPlacedPlantInfo* RowData = PlantDataTable->FindRow<FPlacedPlantInfo>(RowNames[i], TEXT("Plant Info"));
		if (RowData)
		{
			UUserWidget_SeedBankOneCard* NewCard = CreateWidget<UUserWidget_SeedBankOneCard>(this, SeedBankOneCardClass);
			SeedBankCards.Add(NewCard);
			if (NewCard)
			{
				NewCard->SetCardInfo(*RowData, i);
				PlantBox->AddChild(NewCard);
			}
		}
	}
}

void UUserWidget_SeedBank::SelectPlantCard(int32 Index)
{
	if (CurIndex == Index)//�ڶ���ѡ��
	{
		SeedBankCards[Index]->OnSelected();
		CurIndex = -1;
		for (int32 i = 0; i < SeedBankCards.Num(); i++)
		{
			SeedBankCards[i]->OnCanceled();
		}
		PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
		if (PlayerController)
		{
			PlayerController->OnCanceledSelectPlant();
		}
	}
	else//��һ��ѡ��
	{
		CurIndex = Index;
		for (int32 i = 0; i < SeedBankCards.Num(); i++)
		{
			SeedBankCards[i]->OnCanceled();
		}
		SeedBankCards[Index]->OnSelected();
		PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
		if (PlayerController)
		{
			PlayerController->OnSelectedPlant();
		}
	}
}
