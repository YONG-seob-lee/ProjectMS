#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MS_StorageOperationPointComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class PROJECTMS_API UMS_StorageOperationPointComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMS_StorageOperationPointComponent();

	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float aDeltaTime, ELevelTick aTickType, FActorComponentTickFunction* aThisTickFunction) override;

	// Instance
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class AMS_Storage> OwnerStorage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class AMS_StaffAICharacter> AIWorkerInst = nullptr;
};
