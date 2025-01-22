// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_UnitBase.h"
#include "MS_ActorUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ActorUnitBase : public UMS_UnitBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, int32 aUnitTableId, int32 aChildTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	virtual bool CreateUnitActor(const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnitActor() override;

	
protected:
	TObjectPtr<class AMS_Actor> CreateActor(const FVector& aVector, const FRotator& aRotator);

public:
	FORCEINLINE TObjectPtr<AMS_Actor> GetActor() const { return Actor; }
	
private:
	UPROPERTY()
	TObjectPtr<class AMS_Actor> Actor = nullptr;
};
