// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "MS_ModeManager.generated.h"


enum class EMS_UnitState : uint8;

UENUM()
enum class EMS_ControllerModeType : uint8
{
	Normal = 0,
	Rotate = 1,
};

UENUM()
enum class EMS_ModeState : uint8
{
	None = 0,

	Normal = 1,
	Construct = 2,
	StaffManagement = 3,
	CustomerManagement = 4,
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FMS_OnChangeModeDelegate, EMS_ModeState, EMS_ControllerModeType);

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
	
	virtual void ChangeState(EMS_ModeState aModeState);

	
private:
	inline static TObjectPtr<UMS_ModeManager> ModeManager = nullptr;

	TObjectPtr<class UMS_StateMachine> ModeStateMachine;

	EMS_ControllerModeType ControllerModeType;
	
public:
	FMS_OnChangeModeDelegate OnChangeModeDelegate;
	
#define gModeMng (*UMS_ModeManager::GetInstance())
};