// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_Staff.h"
#include "MS_StaffCacheTable.generated.h"

UENUM()
enum class EMS_Gender : uint8
{
	Man = 0,
	Woman = 1,
};

UENUM()
enum class EMS_MBTI : uint8
{
	INFP = 0,
	INFJ,	INTP,	INTJ,	ISFP,	ISFJ,	ISTP,	ISTJ,
	ENFP = 8,
	ENFJ,	ENTP,	ENTJ,	ESFP,	ESFJ,	ESTP,	ESTJ
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
	
	FMS_Staff* GetStaffData(int32 aStaffId);
	void GetStaffDatas(TMap<int32, FMS_Staff*>& aStaffDatas);
private:
	TMap<int32, FMS_Staff*> StaffDatas;
};