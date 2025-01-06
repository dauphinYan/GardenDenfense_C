#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_PlantedArea.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PlantedArea : public AActor
{
	GENERATED_BODY()

public:
	AActor_PlantedArea();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCursorEnter(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnCursorLeave(UPrimitiveComponent* TouchedComponent);

public:
	void SetArrowVisibility(bool bCanSee);

private:
	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* ArrowWidget;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxCollision;

	UPROPERTY()
	class AMainPlayerController* PlayerController;
};
