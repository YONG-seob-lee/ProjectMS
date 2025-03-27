// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_ModeManager.generated.h"


enum class EMS_UnitState : uint8;

DECLARE_MULTICAST_DELEGATE_TwoParams(FMS_OnChangeModeDelegate, EMS_ModeState, EMS_ControllerModeType);
DECLARE_MULTICAST_DELEGATE(FMS_OnUpdateZoneDelegate)
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeManager : public UMS_ManagerBase
{
	GENERATED_BODY()
	
public:
	UMS_ModeManager();

	static UMS_ModeManager* GetInstance();

	// Life Cycle
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void PreFinalize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;

	virtual void Tick(float aDeltaTime);

	
public:
	// ControllerMode
	void ChangeControllerMode(EMS_ControllerModeType aControllerModeType);

private:
	void ShowRotateWidget();
	void HideRotateWidget();

	
private:
	// ModeStateMachine
	void CreateModeStateMachine();
	void DestroyModeStateMachine();

public:
	void RegisterModeState(EMS_ModeState aModeState, const FName& aName, TSubclassOf<class UMS_ModeStateBase> aClassType);

	void UnregisterModeStates();

	TObjectPtr<UMS_ModeStateBase> GetCurrentModeState() const;
	EMS_ModeState GetCurrentModeStateId() const;
	
	void ChangeState(EMS_ModeState aModeState);

	
private:
	inline static TObjectPtr<UMS_ModeManager> ModeManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_StateMachine> ModeStateMachine;

	EMS_ControllerModeType ControllerModeType;
	
public:
	FMS_OnChangeModeDelegate OnChangeModeDelegate;
	FMS_OnUpdateZoneDelegate OnUpdateZoneDelegate;
	
#define gModeMng (*UMS_ModeManager::GetInstance())
};