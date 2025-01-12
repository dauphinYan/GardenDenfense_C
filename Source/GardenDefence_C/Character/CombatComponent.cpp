#include "CombatComponent.h"
#include "MainCharacter.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "GardenDefence_C/Plant/Actor_EquippedPlant.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	EquippedPlantSocketOffset.Add(FVector(100, 0, 50));  // 前面
	EquippedPlantSocketOffset.Add(FVector(50, 50, 50));   // 左前
	EquippedPlantSocketOffset.Add(FVector(0, 100, 50));   // 右前
	EquippedPlantSocketOffset.Add(FVector(-100, 0, 50));  // 后面
	EquippedPlantSocketOffset.Add(FVector(-50, -50, 50)); // 左后
	EquippedPlantSocketOffset.Add(FVector(0, -100, 50));  // 右后

	OwningEquippedPlantNames = { EEquippedPlantName::EPN_None,EEquippedPlantName::EPN_None,EEquippedPlantName::EPN_None,EEquippedPlantName::EPN_None,EEquippedPlantName::EPN_None,EEquippedPlantName::EPN_None };
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	Character = Cast<AMainCharacter>(PlayerController->GetPawn());

	UploadingBaseAsset();
	UpdateEquippedPlant();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::UploadingBaseAsset()
{
	for (EEquippedPlantName Item : SelectedEquippedPlantNameInfos)
	{
		switch (Item)
		{
		case EEquippedPlantName::EPN_Peashooter:
			PlantClasses.Add(Item, StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprint/Plant/EquippedPlant/BP_EquippedPlant_PeaShooter.BP_EquippedPlant_PeaShooter_C'")));
			break;
		case EEquippedPlantName::EPN_Repeater:
			PlantClasses.Add(Item, StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Blueprint'/Game/Blueprint/Plant/EquippedPlant/BP_EquippedPlant_Repeater.BP_EquippedPlant_Repeater_C'")));
			break;
		default:
			break;
		}
	}
}

bool UCombatComponent::AddOwningEquippedPlant(EEquippedPlantName EquippedPlantName, int32 Index)
{
	for (int32 i = 0; i < OwningEquippedPlantNames.Num(); i++)
	{
		if (OwningEquippedPlantNames[i] == EEquippedPlantName::EPN_None)
		{
			OwningEquippedPlantNames[i] = EquippedPlantName;
			PlayerController->RefreshBag();
			return true;
		}
	}
	return false;
}

bool UCombatComponent::RemoveOwningEquippedPlant(EEquippedPlantName EquippedPlantName, int32 Index)
{
	if (Index >= 6) return false;
	if (OwningEquippedPlantNames[Index] != EEquippedPlantName::EPN_None)
	{
		OwningEquippedPlantNames[Index] = EEquippedPlantName::EPN_None;
		PlayerController->RefreshBag();
		return true;
	}
	return false;
}

void UCombatComponent::UpdateEquippedPlant()
{
	for (AActor_EquippedPlant* Equipment : EquippedPlantArray)
	{
		Equipment->Destroy();
	}
	EquippedPlantArray.Empty();
	for (int32 i = 0; i < OwningEquippedPlantNames.Num(); i++)
	{
		if (PlantClasses.Contains(OwningEquippedPlantNames[i]))
		{
			AActor_EquippedPlant* SpawnPlant = GetWorld()->SpawnActor<AActor_EquippedPlant>(PlantClasses[OwningEquippedPlantNames[i]], Character->GetActorLocation() + EquippedPlantSocketOffset[i], FRotator::ZeroRotator);
			SpawnPlant->AttachToActor(Character, FAttachmentTransformRules::KeepWorldTransform);
			EquippedPlantArray.Add(SpawnPlant);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Error, Plant is valid!"));
		}
	}
}

