#pragma once

#include "CoreMinimal.h"
#include "Actor/MS_Actor.h"
#include "MS_Storage.generated.h"

UCLASS() class PROJECTMS_API AMS_Storage : public AMS_Actor
{
	GENERATED_BODY()
	
public:
	AMS_Storage();

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
