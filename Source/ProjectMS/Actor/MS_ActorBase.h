// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
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
	void Create();
	
	void Initialize();
	void Finalize();

	// Unit
	FORCEINLINE void SetOwnerUnitBase(class UMS_UnitBase* aOwnerUnit) { OwnerUnit = aOwnerUnit; }
	FORCEINLINE TWeakObjectPtr<class UMS_UnitBase> GetOwnerUnitBase() const { return OwnerUnit; }

	template <typename T>
	TWeakObjectPtr<T> GetOwnerUnitBase() const
	{
		if (GetOwnerUnitBase() == nullptr)
		{
			return nullptr;
		}
		
		return Cast<T>(GetOwnerUnitBase());
	};

	FORCEINLINE MS_Handle GetUnitHandleId() const { return UnitHandleId; }

	
	// Interaction
	virtual bool HasInteractionComponent() { return false; }
	virtual void OnPressDownEvent() {}
	virtual void OnPressUpEvent() {}
	virtual void LaunchEvent() {}

	
protected:
	// Unit
	MS_Handle UnitHandleId = InvalidUnitHandle;
	
	TWeakObjectPtr<class UMS_UnitBase> OwnerUnit = nullptr;

	
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> SceneRootComponent;
};
