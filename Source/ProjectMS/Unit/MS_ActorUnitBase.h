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
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

	virtual bool CreateUnitActor(const FVector& aPosition, const FRotator& aRotator) override;
	virtual void DestroyUnitActor() override;

	virtual bool SetUnitActor(TObjectPtr<class AMS_ActorBase> aUnitActor, bool bForced = false);

	FVector GetUnitPosition() const;
	
	
protected:
	TObjectPtr<class AMS_ActorBase> CreateActor(const FVector& aVector, const FRotator& aRotator);
	
public:
	FORCEINLINE TObjectPtr<AMS_ActorBase> GetActor() const { return Actor; }

	template<class T>
	TObjectPtr<T> GetActor() const
	{
		return Cast<T>(Actor);
	}
	
private:
	UPROPERTY()
	TObjectPtr<class AMS_ActorBase> Actor = nullptr;
};
