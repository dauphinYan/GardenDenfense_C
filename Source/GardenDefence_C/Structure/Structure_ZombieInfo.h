#pragma once

#include "CoreMinimal.h"
#include "GardenDefence_C/Enum/ZombieName.h"
#include "Structure_ZombieInfo.generated.h"

USTRUCT(BlueprintType)
struct FZombieInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	EZombieName eZombieName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	FText ZombieName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	FText ZombieDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	float AtkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	float Cost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	float CoolingTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zombie Info")
	UTexture2D* ZombieImage;
};
