#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GardenDefence_C/Enum/OperationState.h"
#include "EnhancedInputSubsystems.h"
#include "MainPlayerController.generated.h"

UCLASS()
class GARDENDEFENCE_C_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;
	class AGamePlayHUD* CharacterHUD;

	UFUNCTION(BlueprintCallable)
	void SelectPlantInSeedBank(int32 Index);
	EOperationState OperationState = EOperationState::EOS_Unoccupied;

	UPROPERTY(EditDefaultsOnly, Category = "Plant")
	TSubclassOf<class AActor_PrePlacedPlant> PrePlantClass;

	void OnSelectedPlant();
	void OnCanceledSelectPlant();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	FTimerHandle PrePlantHandle;
	class AActor_PrePlacedPlant* PrePlant;

protected:
	void SetPrePlantLocation();
};
