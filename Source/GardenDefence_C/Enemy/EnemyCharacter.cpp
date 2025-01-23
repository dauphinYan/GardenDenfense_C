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
	TArray<FName> RowNames = ZombieDataTable->GetRowNames();
	for (FName RowName : RowNames)
	{
		FZombieInfo* RowData = ZombieDataTable->FindRow<FZombieInfo>(RowName, TEXT("Zombie Info"));
		Health = RowData->Health;
		Damage = RowData->Damage;
		AtkSpeed = RowData->AtkSpeed;
		MoveSpeed = RowData->MoveSpeed;
	}
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::ReceiveDamage);
}

bool AEnemyCharacter::IsAlive()
{
	return bIsAlive;
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

