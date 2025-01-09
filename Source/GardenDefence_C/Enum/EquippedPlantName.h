#pragma once

UENUM(BlueprintType)
enum class EEquippedPlantName : uint8
{
	EPN_Peashooter UMETA(DisplayName = "Peashooter"),
	EPN_SnowPea UMETA(DisplayName = "Snow Pea"),
	EPN_Chomper UMETA(DisplayName = "Chomper"),
	EPN_Repeater UMETA(DisplayName = "Repeater"),
	EPN_Fumeshroom UMETA(DisplayName = "Fumeshroom"),
	EPN_Gatling UMETA(DisplayName = "Gatling"),
	EPN_None UMETA(DisplayName = "None")
};