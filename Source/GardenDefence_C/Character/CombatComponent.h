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
	void UpdateEquippedPlant();

	UFUNCTION(BlueprintCallable)
	void AddOwningEquippedPlant(EEquippedPlantName EquippedPlantName);

	UFUNCTION(BlueprintCallable)
	void RemoveOwningEquippedPlant(EEquippedPlantName EquippedPlantName);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<EEquippedPlantName> SelectedEquippedPlantNameInfos; //���ѡ��������ѡ��ֲ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<EEquippedPlantName> OwningEquippedPlantNames; //����ѹ����ֲ����Ϣ
private:

	UPROPERTY()
	TMap<EEquippedPlantName, UClass*> PlantClasses; //�����ѡֲ�����ͼ������

	UPROPERTY()
	TArray<class AActor_EquippedPlant*> EquippedPlantArray; //������ɵ�ֲ��Actor

	UPROPERTY(EditAnywhere)
	TArray<FVector> EquippedPlantSocketOffset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor_EquippedPlant> EquippedPlantClass;

	UPROPERTY()
	class AMainCharacter* Character;

	UPROPERTY()
	class AMainPlayerController* PlayerController;
};
