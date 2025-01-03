#include "MainPlayerController.h"
#include "GardenDefence_C/Widget/UserWidget_MainUI.h"
#include "GardenDefence_C/Widget/GamePlayHUD.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CharacterHUD = Cast<AGamePlayHUD>(GetHUD());
}

void AMainPlayerController::SelectPlantInSeedBank(int32 Index)
{
	CharacterHUD->SelectPlantInSeedBank(Index);
}
