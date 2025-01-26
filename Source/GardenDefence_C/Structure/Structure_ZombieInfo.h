#pragma once

#include "CoreMinimal.h"
#include "GardenDefence_C/Enum/ZombieName.h"
#include "Structure_ZombieInfo.generated.h"

USTRUCT(BlueprintType)
struct FZombieInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EZombieName eZombieName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	FText ZombieName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	FText ZombieDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Property")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Property")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Property")
	float AtkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Property")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Property")
	float Cost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Property")
	float CoolingTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Resourse")
	UTexture2D* ZombieImage;
};

USTRUCT(BlueprintType)
struct FZombieEquipment : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EZombieEquipment eZombieEquipment;

	UPROPERTY(EditDefaultsOnly)
	float ArmorValue;
};