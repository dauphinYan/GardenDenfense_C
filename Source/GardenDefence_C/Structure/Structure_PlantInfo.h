#pragma once

#include "CoreMinimal.h"
#include "GardenDefence_C/Enum/PlantName.h"
#include "Structure_PlantInfo.generated.h"

USTRUCT(BlueprintType)
struct FPlantSkillTree : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EEquippedPlantName eEquippedPlantName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 Level;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FText> Description;
};

USTRUCT(BlueprintType)
struct FPlacedPlantInfo :public FTableRowBase
{

	GENERATED_BODY(BlueprintReadWrite)

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EPlacedPlantName PlacedPlantName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Info")
	FText PlantName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Info")
	FText PlantDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Health;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float AtkSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Sun;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Price;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float CoolingTime;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Resourse")
	UTexture2D* PlantImage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Resourse")
	FString MeshPath;
};

USTRUCT(BlueprintType)
struct FEquippedPlantInfo :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EEquippedPlantName eEquippedPlantName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Info")
	FText PlantName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Info")
	FText PlantDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Health;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float AtkSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Sun;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float Price;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Property")
	float CoolingTime;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Plant Resourse")
	UTexture2D* PlantImage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FPlantSkillTree SkillTree;
};

