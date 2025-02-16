// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_CharacterUnitBase.h"
#include "MS_StaffCharacterUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffCharacterUnit : public UMS_CharacterUnitBase
{
	GENERATED_BODY()

public:
	void OnRegistedAsIssueTicketStaff(TWeakObjectPtr<class UMS_IssueTicket> aIssueTicket);
	void OnUnregistedAsIssueTicketStaff();
};
