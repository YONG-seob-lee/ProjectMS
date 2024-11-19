// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreClass/StateMachine/MS_StateBase.h"
#include "Management/UnitManager/MS_UnitManager.h"
#include "MS_SceneStateBase.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FMS_LoadingProcessDelegate, float);

namespace Practice
{
	const FName DefaultCharacter = TEXT("asdf");
	constexpr int32 DefaultCharacterIndex = 1;
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SceneStateBase : public UMS_StateBase
{
	GENERATED_BODY()
	

protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

public:
	void TickLoading(float DeltaTime);
	bool IsCompleteLoading() const;
	FORCEINLINE void WeakBindUnitManager(const TObjectPtr<UMS_UnitManager>& aUnitManager) { UnitManager = aUnitManager; }

protected:
	virtual bool LoadingPreProcess(float DeltaTime);
	virtual bool LoadingProcess(float DeltaTime);
	virtual bool LoadingPostProcess(float DeltaTime);

	TObjectPtr<class AMS_SpawnPoint> GetSpawnPoint(const FName& aCharacterName) const;
	virtual TObjectPtr<class UMS_BasePlayer> CreatePlayer(const TObjectPtr<class AMS_SpawnPoint> aSpawnPoint);
	
private:
	TArray<FMS_LoadingProcessDelegate> LoadingProcessDelegates = {};
	TWeakObjectPtr<UMS_UnitManager> UnitManager = nullptr;
};
