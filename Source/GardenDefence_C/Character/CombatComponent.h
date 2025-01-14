#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GardenDefence_C/Structure/Structure_PlantInfo.h"
#include "GardenDefence_C/Enum/PlantName.h"
#include "CombatComponent.generated.h"

USTRUCT(BlueprintType)
struct FEquippedPlantOrder
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EEquippedPlantName PlantName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 PlantLevel;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GARDENDEFENCE_C_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UploadingBaseAsset();

	UFUNCTION(BlueprintCallable)
	void UpdateEquippedPlant();

	UFUNCTION(BlueprintCallable)
	bool AddOwningEquippedPlant(EEquippedPlantName EquippedPlantName);

	UFUNCTION(BlueprintCallable)
	bool EnhanceOwningEquippedPlant(int32 Index);

	UFUNCTION(BlueprintCallable)
	bool RemoveOwningEquippedPlant(EEquippedPlantName EquippedPlantName, int32 Index);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<EEquippedPlantName> SelectedEquippedPlantNameInfos; // selected plant.

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEquippedPlantOrder> OwningEquippedPlants; // owning plant info: PlantName, PlantLevel.

private:
	UPROPERTY()
	TMap<EEquippedPlantName, UClass*> PlantClasses; // plant class.

	UPROPERTY()
	TArray<class AActor_EquippedPlant*> EquippedPlantArray; // spawned plant actors.

	UPROPERTY(EditAnywhere)
	TArray<FVector> EquippedPlantSocketOffset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor_EquippedPlant> EquippedPlantClass;

	UPROPERTY()
	class AMainCharacter* Character;

	UPROPERTY()
	class AMainPlayerController* PlayerController;
};
