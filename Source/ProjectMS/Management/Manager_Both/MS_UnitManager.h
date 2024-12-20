// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "Management/MS_ManagerBase.h"
#include "Utility/MS_Define.h"
#include "MS_UnitManager.generated.h"

UENUM()
enum EMS_UnitType
{
	Default = 0,
	BasePlayer = 1,
	Item = 2,
	Furniture = 3,
	Prop = 4,
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitManager : public UMS_ManagerBase
{
	GENERATED_BODY()

public:
	UMS_UnitManager();
	virtual void Finalize() override;
	void DestroyAllUnits();
	
	TObjectPtr<class UMS_UnitBase> CreateUnit(int32 aUnitTableId, const TSubclassOf<UMS_UnitBase>& aUnitType, const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);
	TObjectPtr<class UMS_UnitBase> CreateUnit(int32 aUnitTableId, int32 aUnitType, const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);

	TObjectPtr<class AMS_CharacterBase> CreateCharacter(const FString& aBlueprintPath, const FVector& aPosition, const FRotator& aRotator);

	TObjectPtr<AMS_Actor> CreateActor(const FString& aBlueprintPath, const FVector& aVector, const FRotator& aRotator);

	
	TObjectPtr<AActor> SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent = true,
											   ESpawnActorCollisionHandlingMethod Method = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn) const;

private:

	UPROPERTY()
	TMap<int32, TObjectPtr<UMS_UnitBase>> Units;

public:
	inline static TObjectPtr<UMS_UnitManager> UnitManager = nullptr;
	static UMS_UnitManager* GetInstance();

	TMap<EMS_UnitType, TSubclassOf<UMS_UnitBase>> UnitType;
#define gUnitMng (*UMS_UnitManager::GetInstance())
};
