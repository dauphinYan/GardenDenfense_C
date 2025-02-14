#include "DetectTargetBTDecorator.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Math/Vector.h"

bool UDetectTargetBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        AActor* Target = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("Target"));
        if (Target)
        {
            FVector ForwardVector = AIController->GetPawn()->GetActorForwardVector();
            FVector DirectionToTarget = Target->GetActorLocation() - AIController->GetPawn()->GetActorLocation();
            DirectionToTarget.Normalize();

            float DotProduct = FVector::DotProduct(ForwardVector, DirectionToTarget);

            const float MinDotProduct = FMath::Cos(FMath::DegreesToRadians(45.0f));
            const float MaxDotProduct = 1.0f;

            return DotProduct >= MinDotProduct;
        }
    }

    return false;
}

