#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GardenDefence_C/Structure/Structure_ZombieInfo.h"
#include "GardenDefence_C/Enum/ZombieName.h"
#include "GardenDefence_C/Interface/Interface_Enemy.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AEnemyCharacter : public ACharacter, public IInterface_Enemy
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual bool IsAlive() override;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ZombieDataTable;

	EZombieName ZombieName = EZombieName::EZN_Zombie;
	EZombieEquipment ZombieEquipment = EZombieEquipment::EZE_None;

	float Health = 0;
	float Damage = 1;
	float AtkSpeed = 1;
	float MoveSpeed = 0;

	virtual void ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser) = 0;
private:
	bool bIsAlive = true;
};
