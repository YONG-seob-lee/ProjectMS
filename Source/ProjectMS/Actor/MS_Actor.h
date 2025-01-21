// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ItemUnit.h"

#include "MS_Actor.generated.h"

UCLASS()
class PROJECTMS_API AMS_Actor : public AActor
{
	GENERATED_BODY()

public:
	AMS_Actor(const FObjectInitializer& aObjectInitializer);
	
protected:
	virtual void BeginPlay() override;

public:
	void Create(const FString& aLabelName);
	
	void Initialize();
	void Finalize();
	
	FORCEINLINE void SetOwnerUnitBase(const TObjectPtr<UObject>& aOwner) { UnitOwner = aOwner; }
	FORCEINLINE TWeakObjectPtr<UObject> GetOwnerUnitBase() const { return UnitOwner; }
	
	virtual bool HasInteractionComponent() { return false; }
	virtual void OnPressDownEvent() {}
	virtual void OnPressUpEvent() {}
	virtual void LaunchEvent() {}

	FORCEINLINE MS_Handle GetUnitHandleId() const { return UnitHandleId; }

	
protected:
	MS_Handle UnitHandleId = InvalidUnitHandle;
	
private:
	TWeakObjectPtr<UObject> UnitOwner = nullptr;

protected:
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> SceneRootComponent;

};
