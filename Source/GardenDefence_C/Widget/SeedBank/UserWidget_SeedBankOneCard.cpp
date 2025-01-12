#include "UserWidget_SeedBankOneCard.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "Sound/SoundWave.h"

void UUserWidget_SeedBankOneCard::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonChoose)
	{
		ButtonChoose->OnClicked.AddDynamic(this, &UUserWidget_SeedBankOneCard::OnButtonChooseClicked);
	}
	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
}

void UUserWidget_SeedBankOneCard::OnButtonChooseClicked()
{
	if (PlayerController == nullptr) return;
	PlayerController->SelectPlantInSeedBank(Index);
}

void UUserWidget_SeedBankOneCard::SetCardInfo(FPlacedPlantInfo InPlacedPlantInfo, int32 InIndex)
{
	Index = InIndex;
	PlacedPlantInfo = InPlacedPlantInfo;
	PlantImage->SetBrushResourceObject(PlacedPlantInfo.PlantImage);
	SunText->SetText(FText::AsNumber(PlacedPlantInfo.Sun));
}

void UUserWidget_SeedBankOneCard::OnSelected()
{
	PlayAnimation(OnSelectedAnimation);
}

void UUserWidget_SeedBankOneCard::BeginCool()
{
	bIsCool = true;
	PlayAnimation(CoolingAnimation);
	UKismetSystemLibrary::Delay(this, PlacedPlantInfo.CoolingTime, FLatentActionInfo());
}

void UUserWidget_SeedBankOneCard::OnCanceled()
{
	PlayAnimation(OnCanceledAnimation);
}