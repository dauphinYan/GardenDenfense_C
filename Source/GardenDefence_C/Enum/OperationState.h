#pragma once

UENUM(BlueprintType)
enum class EOperationState :uint8
{
	EOS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EOS_SelectingPlant UMETA(DisplayName = "SelectingPlant"),
	EOS_Shovel UMETA(DisplayName = "Shovel"),
	EOS_MAX UMETA(DisplayName = "DefaultMAX")
};