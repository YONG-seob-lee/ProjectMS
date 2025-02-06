// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_TutorialHelper.generated.h"

UENUM()
enum class EMS_FirstEnterCheckType : uint8
{
	Default = 0,
	Market = 1,
	Schedule = 2,
	Open = 3,
	ConstructMode = 4,
	Hire = 5,
	StaffManage = 6,
	CustomerManage = 7,
	FinancialIndicator = 8,
	Timer = 9,
	StorageInputItem = 10,
	PurchaseFurniture = 11,
	MoveFurniture = 12,
	Close = 13,
	OrderItem = 14,
	StockItem = 15,
	
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TutorialHelper : public UObject
{
	GENERATED_BODY()
public:
	void Initialize();
	void Destroyed();
	
private:
	TMap<EMS_FirstEnterCheckType, bool> FirstEnterCheckContainer;
};
