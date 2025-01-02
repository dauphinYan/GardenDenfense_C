#include "UserWidget_SeedBank.h"
#include "UserWidget_SeedBankOneCard.h"
#include "Components/HorizontalBox.h"


void UUserWidget_SeedBank::NativeConstruct()
{
	Super::NativeConstruct();

	UpdatePlantBox();
}

void UUserWidget_SeedBank::UpdatePlantBox()
{
	if (!SeedBankOneCardClass)
		return;
	PlantBox->ClearChildren();
	const FString DataTablePath = TEXT("DataTable'/Game/Blueprint/DataTable/DT_PlacedPlantInfo.DT_PlacedPlantInfo'");
	UDataTable* PlantDataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
	if (PlantDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable at path: %s"), *DataTablePath);
		return;
	}
	TArray<FName> RowNames = PlantDataTable->GetRowNames();
	for (FName RowName : RowNames)
	{
		FPlacedPlantInfo* RowData = PlantDataTable->FindRow<FPlacedPlantInfo>(RowName, TEXT("Plant Info"));
		if (RowData)
		{
			UUserWidget_SeedBankOneCard* NewCard = CreateWidget<UUserWidget_SeedBankOneCard>(this, SeedBankOneCardClass);
			if (NewCard)
			{
				NewCard->SetCardInfo(*RowData);
				PlantBox->AddChild(NewCard);
			}
		}
	}
}
