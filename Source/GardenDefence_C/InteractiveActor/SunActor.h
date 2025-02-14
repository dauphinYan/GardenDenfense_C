#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "SunActor.generated.h"

UCLASS()
class GARDENDEFENCE_C_API ASunActor : public AActor
{
	GENERATED_BODY()

	friend class AActor_PlacedPlant_SunFlower;

public:
	ASunActor();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION()
	void MeshOnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);

	void SelectSun();

	UPROPERTY(EditDefaultsOnly)
	float SunValue = 25;

	class AMainGameStateBase* GameState;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SunMesh;

	APlayerController* PlayerController;
};
