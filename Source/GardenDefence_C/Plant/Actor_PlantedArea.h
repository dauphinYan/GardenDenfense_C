#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GardenDefence_C/Interface/Interface_PlantedArea.h"
#include "GardenDefence_C/Enum/PlacedPlantName.h"
#include "Actor_PlantedArea.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PlantedArea : public AActor, public IInterface_PlantedArea
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
	virtual void GrowPlant(EPlacedPlantName InPlacedPlantName) override;
	virtual void RemovePlant() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* ArrowWidget;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxCollision;

	UPROPERTY()
	class AMainPlayerController* PlayerController;

	UPROPERTY()
	AActor* Plant;

	bool bIsPlanted = false;
};
