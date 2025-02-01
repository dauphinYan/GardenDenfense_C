#include "AnimInstance_Zombie.h"
#include "GardenDefence_C/Enemy/Zombie/EnemyCharacter_Zombie.h"
#include "GardenDefence_C/Enemy/Zombie/ZombieController.h"

void UAnimInstance_Zombie::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ZombieCharacter = Cast<AEnemyCharacter_Zombie>(TryGetPawnOwner());
	if (ZombieCharacter)
		ZombieController = Cast<AZombieController>(ZombieCharacter->GetController());
}

void UAnimInstance_Zombie::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	ZombieCharacter = ZombieCharacter == nullptr ? Cast<AEnemyCharacter_Zombie>(TryGetPawnOwner()) : ZombieCharacter;
	if (ZombieCharacter == nullptr) return;
	FVector Velocity = ZombieCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();

	if (ZombieCharacter)
		ZombieController = ZombieController == nullptr ? Cast<AZombieController>(ZombieCharacter->GetController()) : ZombieController;
	if (ZombieController == nullptr) return;
	bIsAttacking = ZombieController->GetAttackingBool();
}
