#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GardenDefence_C/Enum/OperationState.h"
#include "GardenDefence_C/Enum/PlacedPlantName.h"
#include "EnhancedInputSubsystems.h"
#include "MainPlayerController.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnCanceledButtonPressed();

	UPROPERTY()
	class AGamePlayHUD* CharacterHUD;

	UFUNCTION(BlueprintCallable)
	void SelectPlantInSeedBank(int32 Index);
	EOperationState OperationState = EOperationState::EOS_Unoccupied;

	UPROPERTY(EditDefaultsOnly, Category = "Plant")
	TSubclassOf<class AActor_PrePlacedPlant> PrePlantClass;

	void OnSelectedPlant(EPlacedPlantName InPlacedPlantName);
	void OnCanceledSelectPlant();
	void GrowPlacedPlant();


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputAction* IA_Cancel;

	UPROPERTY()
	FTimerHandle PrePlantHandle;
	UPROPERTY()
	class AActor_PrePlacedPlant* PrePlant;
	UPROPERTY()
	FTimerHandle DetectPlantAreaHandle;
	UPROPERTY()
	AActor* PlacedPlantArea;

	UPROPERTY()
	class USoundWave* GrowSoundWave;

protected:
	void SetPrePlantLocation();
};
