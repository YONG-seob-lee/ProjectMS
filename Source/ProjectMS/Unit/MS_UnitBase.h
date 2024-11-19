// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMS/Actor/Character/MS_CharacterBase.h"
#include "ProjectMS/Data/Table/RowBase/MS_ResourceUnit.h"
#include "ProjectMS/Utility/MS_Define.h"
#include "UObject/Object.h"
#include "MS_UnitBase.generated.h"

// 플레이어 인풋 스테이트를 관리하기 위한 열거형
UENUM(BlueprintType)
enum class EMS_UnitState : uint8
{
	None = 0					UMETA(DisplayName = "None"),
	Player_Normal				UMETA(DisplayName = "Player_Normal"),
};

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
	FORCEINLINE TObjectPtr<AMS_CharacterBase> GetCharacterBase() const { return Character; }

	void CreateUnitStateMachine();
	void RegisterUnitState(EMS_UnitState aState, const FName& aName, TSubclassOf<class UMS_StateBase> aClassType);
	TObjectPtr<UMS_StateBase> GetCurrentUnitState() const;

	void SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine) const;
	
protected:
	virtual void ChangeActionState(EMS_UnitState aActionType) const;
	
	MS_Handle UnitHandle = InvalidUnitHandle;
	
	FMS_ResourceUnit* UnitData = nullptr;

	UPROPERTY()
	TObjectPtr<AMS_CharacterBase> Character = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_StateMachine> UnitStateMachine = nullptr;
};
