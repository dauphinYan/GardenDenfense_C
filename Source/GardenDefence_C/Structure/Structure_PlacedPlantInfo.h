#pragma once

#include "CoreMinimal.h"
#include "Structure_PlacedPlantInfo.generated.h"

// 定义结构体
USTRUCT(BlueprintType)
struct FPlacedPlantInfo :public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	FText PlantName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	FText PlantDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	float Sun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	float Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	float CoolingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	UTexture2D* PlantImage;

	
};
