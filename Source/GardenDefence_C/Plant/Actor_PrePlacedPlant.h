#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_PrePlacedPlant.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AActor_PrePlacedPlant : public AActor
{
	GENERATED_BODY()

public:
	AActor_PrePlacedPlant();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Plant Asset")
	UStaticMeshComponent* PlantMesh;

public:
	virtual void Tick(float DeltaTime) override;

};
