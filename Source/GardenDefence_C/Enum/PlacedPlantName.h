#pragma once

UENUM(BlueprintType)
enum class EPlacedPlantName : uint8
{
	PPN_SunFlower UMETA(DisplayName = "SunFlower"),
	PPN_WallNut UMETA(DisplayName = "WallNut"),
	PPN_Potatomine UMETA(DisplayName = "Potatomine"),
	PPN_CherryBomb UMETA(DisplayName = "CherryBomb"),
	PPN_SpikeWeed UMETA(DisplayName = "SpikeWeed"),
	PPN_TorchStump UMETA(DisplayName = "TorchStump"),
	PPN_DefaultMax UMETA(DisplayName = "DefaultMax")
};