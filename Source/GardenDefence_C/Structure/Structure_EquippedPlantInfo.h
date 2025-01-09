#pragma once

#include "CoreMinimal.h"
#include "GardenDefence_C/Enum/EquippedPlantName.h"
#include "Structure_EquippedPlantInfo.generated.h"

USTRUCT(BlueprintType)
struct FEquippedPlantInfo :public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	EEquippedPlantName eEquippedPlantName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	FText PlantName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	FText PlantDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	float AtkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	float Sun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	float Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	float CoolingTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plant Info")
	UTexture2D* PlantImage;
};
