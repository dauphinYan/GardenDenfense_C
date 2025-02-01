#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CoinActor.generated.h"

UCLASS()
class GARDENDEFENCE_C_API ACoinActor : public AActor
{
	GENERATED_BODY()

public:
	ACoinActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(EditDefaultsOnly)
	int32 CoinValue = 10;

	UFUNCTION()
	void UpdateCoinPosition(float Value);

	UFUNCTION()
	void OnSelectTimelineFinished();

	UFUNCTION()
	void MeshOnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnSelect();

private:
	UPROPERTY(EditDefaultsOnly)
	USoundWave* SelectedSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CoinWidgetClass;

	UUserWidget* CoinWidget;

	APlayerController* PlayerController;

	UPROPERTY()
	FTimeline MoveTimeline;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* MoveCurve;

	FOnTimelineFloat MoveFunction;

	FVector2D StartPosition;
	FVector2D EndPosition = FVector2D(50, -50);

	FOnTimelineEvent SelectTimelineFinishedEvent;
};
