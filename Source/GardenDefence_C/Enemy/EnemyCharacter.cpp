#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ZombieDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load ZombieInfoDataTable"));
		return;
	}
	TArray<FName> ZombieNames = ZombieDataTable->GetRowNames();
	for (FName RowName : ZombieNames)
	{
		FZombieInfo* RowData = ZombieDataTable->FindRow<FZombieInfo>(RowName, TEXT("Zombie Info"));
		if (RowData->eZombieName != ZombieName) continue;
		Health = RowData->Health;
		AtkDamage = RowData->Damage;
		AtkSpeed = RowData->AtkSpeed;
		MoveSpeed = RowData->MoveSpeed;
	}
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	if (ZombieEquipmentDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load ZombieInfoDataTable"));
		return;
	}
	TArray<FName> ZombieEquipmentNames = ZombieEquipmentDataTable->GetRowNames();
	for (FName RowName : ZombieEquipmentNames)
	{
		FZombieEquipment* RowData = ZombieEquipmentDataTable->FindRow<FZombieEquipment>(RowName, TEXT("Zombie Equipment"));
		if (RowData->eZombieEquipment != ZombieEquipment) continue;
		ArmorValue = RowData->ArmorValue;
	}

	OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::ReceiveDamage);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AEnemyCharacter::IsAlive()
{
	return bIsAlive;
}

void AEnemyCharacter::ReceiveDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser)
{

}

void AEnemyCharacter::OnArmorDestroyed()
{

}

void AEnemyCharacter::OnEnemyDied()
{
	Destroy();
}

void AEnemyCharacter::AttackTarget()
{

}