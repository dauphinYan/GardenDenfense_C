#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2
#define ECC_PlacedPlant ECollisionChannel::ECC_GameTraceChannel3

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieController.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AZombieController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void SearchTarget();

	FTimerHandle SearchHandle;
	AActor* BestTarget;
	AActor* HomeTarget;

	UPROPERTY(EditDefaultsOnly)
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;
};
