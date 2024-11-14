// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMS/Actor/Character/MS_CharacterBase.h"
#include "ProjectMS/Data/Table/RowBase/MS_ResourceUnit.h"
#include "ProjectMS/Utility/MS_Define.h"
#include "UObject/Object.h"
#include "MS_UnitBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize();
	virtual void Finalize();
	virtual void PostInitialize();
	virtual void Tick(float aDeltaTime);
	
	virtual bool CreateUnit(int32 aUnitTableId, const FVector& aPos = FVector::ZeroVector, const FRotator& aRot = FRotator::ZeroRotator);
	virtual void DestroyUnit();
	
	FORCEINLINE void SetUnitHandle(MS_Handle aUnitHandle) { UnitHandle = aUnitHandle; }
	FORCEINLINE MS_Handle GetUnitHandle() const { return UnitHandle; }

private:
	MS_Handle UnitHandle = InvalidUnitHandle;
	
	FMS_ResourceUnit* UnitData = nullptr;

	UPROPERTY()
	TObjectPtr<AMS_CharacterBase> Character = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_StateMachine> ActionStateMachine = nullptr;
};
