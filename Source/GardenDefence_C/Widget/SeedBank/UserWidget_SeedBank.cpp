#include "UserWidget_SeedBank.h"
#include "UserWidget_SeedBankOneCard.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "GardenDefence_C/Enum/OperationState.h"
#include "GardenDefence_C/GamePlay/MainGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UserWidget_Shovel.h"


void UUserWidget_SeedBank::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	UpdatePlantBox();

	SelectSoundWave = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/Audio/SoundEffect/Plant/SelectPlant.SelectPlant'"));
	PauseSoundWave = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/Audio/SoundEffect/UI/pause.pause'"));

	W_Shovel = CreateWidget<UUserWidget_Shovel>(PlayerController, W_ShovelClass, "Shovel");
	W_Shovel->AddToViewport();
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
	if (CurIndex == Index)//第二次选择
	{
		//OnCanceledSelect();
	}
	else//第一次选择
	{
		GameState = GameState == nullptr ? GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;
		if (GameState->GetSunValue() < SeedBankCards[Index]->GetSunValue())
		{
			if (PauseSoundWave)
			{
				UGameplayStatics::PlaySound2D(this, PauseSoundWave);
			}
			return;
		}
		CurIndex = Index;
		for (int32 i = 0; i < SeedBankCards.Num(); i++)
		{
			SeedBankCards[i]->OnCanceled();
		}

		if (SelectSoundWave)
		{
			UGameplayStatics::PlaySound2D(this, SelectSoundWave);
		}
		SeedBankCards[Index]->OnSelected();
		PlayerController = PlayerController == nullptr ? Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController()) : PlayerController;
		if (PlayerController)
		{
			PlayerController->OnSelectedPlant(SeedBankCards[Index]->GetPlantName());
		}
	}
}

void UUserWidget_SeedBank::OnCanceledSelectPlantCard()
{
	CurIndex = -1;
	for (int32 i = 0; i < SeedBankCards.Num(); i++)
	{
		SeedBankCards[i]->OnCanceled();
	}
}

void UUserWidget_SeedBank::OnSelectedShovel()
{
	W_Shovel->OnSelectedShovel();
	Image_Shovel->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidget_SeedBank::OnCanceledShovel()
{
	W_Shovel->OnCanceledShovel();
	Image_Shovel->SetVisibility(ESlateVisibility::Visible);
}

void UUserWidget_SeedBank::UpdateSunValue()
{
	GameState = GameState == nullptr ? GameState = Cast<AMainGameStateBase>(GetWorld()->GetGameState()) : GameState;
	int32 SunValueInteger = FMath::FloorToInt(GameState->GetSunValue());
	FString SunValueString = FString::FromInt(SunValueInteger);
	SunValueText->SetText(FText::FromString(SunValueString));
}
