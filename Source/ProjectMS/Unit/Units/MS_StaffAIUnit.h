// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_AIUnit.h"
#include "MS_StaffAIUnit.generated.h"

enum class EMS_PersonalActionType;
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffAIUnit : public UMS_AIUnit
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual int32 GetBlueprintPathId() const override;
	virtual UClass* GetBlueprintClass() const override;

public:
	void RegisterPersonalAction(EMS_PersonalActionType aPersonalActionType);
	void UnregisterPersonalAction(EMS_PersonalActionType aPersonalActionType);
	
	void OnRegistedAsIssueTicketStaff(TWeakObjectPtr<class UMS_IssueTicket> aIssueTicket);
	void OnUnregistedAsIssueTicketStaff();

private:
	struct FMS_Staff* StaffTableData = nullptr;

	TArray<EMS_PersonalActionType> PersonalActions;
	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;
};
