#include "Wallnut.h"

AWallnut::AWallnut()
{
	PlacedPlantName = EPlacedPlantName::PPN_WallNut;
}

void AWallnut::ReceiveDamage(AActor* DamageActor, float InDamage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	if (Health - InDamage > 0)
	{
		Health -= InDamage;
	}
	else
	{
		OnPlantDestroyed();
	}
}

