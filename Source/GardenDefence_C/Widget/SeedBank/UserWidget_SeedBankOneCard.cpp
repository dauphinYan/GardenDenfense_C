#include "UserWidget_SeedBankOneCard.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUserWidget_SeedBankOneCard::SetCardInfo(FPlacedPlantInfo InPlacedPlantInfo)
{
	PlantImage->SetBrushResourceObject(InPlacedPlantInfo.PlantImage);
	SunText->SetText(FText::AsNumber(InPlacedPlantInfo.Sun));
}
