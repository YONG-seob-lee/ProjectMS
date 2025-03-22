// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "MS_UnitBase.h"

#include "MS_ActorBase.generated.h"

UCLASS()
class PROJECTMS_API AMS_ActorBase : public AActor
{
	GENERATED_BODY()

public:
	AMS_ActorBase(const FObjectInitializer& aObjectInitializer);
	
protected:
	virtual void BeginPlay() override;

public:
	void Create(const FString& aLabelName);
	
	void Initialize();
	void Finalize();
	
	FORCEINLINE void SetOwnerUnitBase(class UMS_UnitBase* aOwnerUnit) { OwnerUnit = aOwnerUnit; }
	FORCEINLINE TWeakObjectPtr<class UMS_UnitBase> GetOwnerUnitBase() const { return OwnerUnit; }
	
	virtual bool HasInteractionComponent() { return false; }
	virtual void OnPressDownEvent() {}
	virtual void OnPressUpEvent() {}
	virtual void LaunchEvent() {}

	FORCEINLINE MS_Handle GetUnitHandleId() const { return UnitHandleId; }

	
protected:
	MS_Handle UnitHandleId = InvalidUnitHandle;
	
	TWeakObjectPtr<class UMS_UnitBase> OwnerUnit = nullptr;

protected:
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> SceneRootComponent;
};
