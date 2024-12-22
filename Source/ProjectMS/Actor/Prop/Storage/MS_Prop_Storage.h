#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/MS_Prop.h"
#include "MS_Prop_Storage.generated.h"

UCLASS() class PROJECTMS_API AMS_Prop_Storage : public AMS_Prop
{
	GENERATED_BODY()
	
public:
	AMS_Prop_Storage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UStaticMeshComponent> StorageStaticMeshComponent = nullptr;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UMS_StorageOperationSpotComponent> OperationSpotComponent = {};
};
