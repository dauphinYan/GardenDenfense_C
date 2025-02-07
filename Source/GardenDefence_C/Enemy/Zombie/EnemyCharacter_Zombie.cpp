#include "EnemyCharacter_Zombie.h"
#include "ZombieController.h"

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
	ZombieController = ZombieController == nullptr ? Cast<AZombieController>(GetController()) : ZombieController;
	if (ZombieController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get zombiecontroller!"));
		return;
	}
	AActor* Target = ZombieController->BestTarget;
	if (Target)
	{
		UGameplayStatics::ApplyDamage(
			Target,
			AtkDamage,
			ZombieController,
			this,
			UDamageType::StaticClass()
		);
	}

}

void AEnemyCharacter_Zombie::OnArmorDestroyed()
{

}

void AEnemyCharacter_Zombie::OnEnemyDied()
{
	Super::OnEnemyDied();

}

