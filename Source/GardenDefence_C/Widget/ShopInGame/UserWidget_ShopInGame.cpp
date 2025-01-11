#include "UserWidget_ShopInGame.h"
#include "GardenDefence_C/Character/MainCharacter.h"
#include "GardenDefence_C/Character/CombatComponent.h"
#include "Components/Button.h"

void UUserWidget_ShopInGame::NativeConstruct()
{
	Super::NativeConstruct();

	GetNecObject();

}

void UUserWidget_ShopInGame::GetNecObject()
{
	Character = Character == nullptr ? Character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : Character;
	CombatComponent = CombatComponent == nullptr ? CombatComponent = Character->GetCombatComponent() : CombatComponent;
}
