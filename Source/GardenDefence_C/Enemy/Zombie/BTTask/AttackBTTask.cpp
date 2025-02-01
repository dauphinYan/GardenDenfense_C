#include "AttackBTTask.h"
#include "GardenDefence_C/Enemy/Zombie/ZombieController.h"

EBTNodeResult::Type UAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AZombieController* ZombieController = Cast<AZombieController>(AIController);
		if (ZombieController)
		{
			ZombieController->SetCharacterAttackingBool(true);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
