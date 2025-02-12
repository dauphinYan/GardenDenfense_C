#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2
#define ECC_PlacedPlant ECollisionChannel::ECC_GameTraceChannel3

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieController.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AZombieController : public AAIController
{
	friend class AEnemyCharacter_Zombie;

	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetCharacterAttackingBool(bool InBool);


protected:
	virtual void SearchTarget();

	FTimerHandle SearchHandle;
	AActor* BestTarget;

	UPROPERTY(EditDefaultsOnly)
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

private:
	bool bIsAttacking = false;

public:
	FORCEINLINE bool GetAttackingBool() { return bIsAttacking; }
};
