#include "EndAttackBTTask.h"
#include "GardenDefence_C/Enemy/Zombie/ZombieController.h"

EBTNodeResult::Type UEndAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AZombieController* ZombieController = Cast<AZombieController>(AIController);
		if (ZombieController)
		{
			ZombieController->SetCharacterAttackingBool(false);
		}
	}

	return EBTNodeResult::Succeeded;
}
