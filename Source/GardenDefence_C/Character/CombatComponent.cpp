#include "CombatComponent.h"
#include "MainCharacter.h"
#include "GardenDefence_C/GamePlay/MainPlayerController.h"
#include "GardenDefence_C/Plant/Actor_EquippedPlant.h"
#include "GardenDefence_C/Enum/EquippedPlantName.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	EquippedPlantSocketOffset.Add(FVector(100, 0, 50));  // 前面
	EquippedPlantSocketOffset.Add(FVector(50, 50, 50));   // 左前
	EquippedPlantSocketOffset.Add(FVector(0, 100, 50));   // 右前
	EquippedPlantSocketOffset.Add(FVector(-100, 0, 50));  // 后面
	EquippedPlantSocketOffset.Add(FVector(-50, -50, 50)); // 左后
	EquippedPlantSocketOffset.Add(FVector(0, -100, 50));  // 右后
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
	for (FEquippedPlantInfo Item : EquippedPlantNameInfos)
	{
		switch (Item.eEquippedPlantName)
		{
		case EEquippedPlantName::EPN_Peashooter:
			PlantClasses.Add(Item.eEquippedPlantName, StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprint/Plant/EquippedPlant/BP_EquippedPlant_PeaShooter.BP_EquippedPlant_PeaShooter_C'")));
			break;
		case EEquippedPlantName::EPN_Repeater:
			PlantClasses.Add(Item.eEquippedPlantName, StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Blueprint'/Game/Blueprint/Plant/EquippedPlant/BP_EquippedPlant_Repeater.BP_EquippedPlant_Repeater_C'")));
			break;
		default:
			break;
		}
	}
}

void UCombatComponent::UpdateEquippedPlant()
{
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

