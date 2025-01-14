#pragma once

UENUM(BlueprintType)
enum class EEquippedPlantName : uint8
{
	EPN_Peashooter UMETA(DisplayName = "Peashooter"),
	EPN_SnowPea UMETA(DisplayName = "SnowPea"),
	EPN_Chomper UMETA(DisplayName = "Chomper"),
	EPN_Repeater UMETA(DisplayName = "Repeater"),
	EPN_Fumeshroom UMETA(DisplayName = "Fumeshroom"),
	EPN_Gatling UMETA(DisplayName = "Gatling"),
	EPN_KernelPult UMETA(DisplayName = "KernelPult"),
	EPN_MelonPult UMETA(DisplayName = "MelonPult"),
	EPN_WinterMelon UMETA(DisplayName = "WinterMelon"),
	EPN_None UMETA(DisplayName = "None")
};

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