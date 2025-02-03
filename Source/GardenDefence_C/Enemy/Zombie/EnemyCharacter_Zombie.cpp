#include "EnemyCharacter_Zombie.h"

void AEnemyCharacter_Zombie::ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	if (!bIsAlive) return;

	if (ArmorValue > 0)
	{
		ArmorValue -= Damage;
		if (ArmorValue <= 0)
		{
			ArmorValue = 0;
			OnArmorDestroyed();
		}
	}
	else
	{
		Health = Health - Damage;
		if (Health <= 0)
		{
			Health = 0;
			OnEnemyDied();
		}
	}
}

void AEnemyCharacter_Zombie::AttackTarget()
{
	
}

void AEnemyCharacter_Zombie::OnArmorDestroyed()
{

}

void AEnemyCharacter_Zombie::OnEnemyDied()
{
	Super::OnEnemyDied();

}

