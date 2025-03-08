// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_FurnitureUnit.h"
#include "MS_CounterUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CounterUnit : public UMS_FurnitureUnit
{
	GENERATED_BODY()

public:
	bool RegisterCustomerUnit(TWeakObjectPtr<class UMS_CustomerAIUnit> aCustomerUnit);
	void UnregisterCustomerUnit(TWeakObjectPtr<class UMS_CustomerAIUnit> aCustomerUnit);
	
	bool RegisterStaffUnit(TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);
	void UnregisterStaffUnit(TWeakObjectPtr<class UMS_StaffAIUnit> aStaffUnit);

	TWeakObjectPtr<class UMS_CustomerAIUnit> GetFirstCustomerUnit() const;
	TWeakObjectPtr<class UMS_StaffAIUnit> GetStaffUnit(bool bIncludeIssueStaffUnit = true) const;

	// IssueTickets
	virtual void UpdateIssueTicket() override;
	
private:
	TArray<TWeakObjectPtr<class UMS_CustomerAIUnit>> CustomerUnits;
	TWeakObjectPtr<class UMS_StaffAIUnit> StaffUnit;
};
