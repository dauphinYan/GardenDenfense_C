#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GardenDefence_C/Structure/Structure_EquippedPlantInfo.h"
#include "GardenDefence_C/Enum/EquippedPlantName.h"
#include "CombatComponent.generated.h"


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
	bool RemoveOwningEquippedPlant(EEquippedPlantName EquippedPlantName);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<EEquippedPlantName> SelectedEquippedPlantNameInfos; //存放选卡界面已选的植物

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<EEquippedPlantName> OwningEquippedPlantNames; //存放已购买的植物信息
private:
	UPROPERTY()
	TMap<EEquippedPlantName, UClass*> PlantClasses; //存放已选植物的蓝图类索引

	UPROPERTY()
	TArray<class AActor_EquippedPlant*> EquippedPlantArray; //存放生成的植物Actor

	UPROPERTY(EditAnywhere)
	TArray<FVector> EquippedPlantSocketOffset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor_EquippedPlant> EquippedPlantClass;

	UPROPERTY()
	class AMainCharacter* Character;

	UPROPERTY()
	class AMainPlayerController* PlayerController;
};
