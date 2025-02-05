// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId);
	virtual void Finalize();
	virtual void PostInitialize();
	virtual void Tick(float aDeltaTime);

	void DestroyUnit();
	
	virtual bool CreateUnitActor(const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);
	virtual void DestroyUnitActor();
	
	FORCEINLINE MS_Handle GetUnitHandle() const { return UnitHandle; }
	FORCEINLINE EMS_UnitType GetUnitType() const { return UnitType; }
	
protected:
	TSubclassOf<UClass> GetBlueprintClass() { return ClassType; }
	
	TObjectPtr<AActor> MS_SpawnActor(UClass* aClass, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent = true,
										   ESpawnActorCollisionHandlingMethod Method = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn) const;

	
	// Unit State Machine
public:
	void CreateUnitStateMachine();
	void RegisterUnitState(EMS_UnitState aState, const FName& aName, TSubclassOf<class UMS_StateBase> aClassType);
	TObjectPtr<UMS_StateBase> GetCurrentUnitState() const;

protected:
	virtual void ChangeState(EMS_UnitState aUnitState) const;


protected:
	MS_Handle UnitHandle = InvalidUnitHandle;

	UPROPERTY()
	int32 UnitTableId = INDEX_NONE;
	
	EMS_UnitType UnitType = EMS_UnitType::Default;
	TSubclassOf<UClass> ClassType = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_StateMachine> UnitStateMachine = nullptr;
};
