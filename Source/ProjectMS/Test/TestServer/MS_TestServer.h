// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_TestServer.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TestServer : public UObject
{
	GENERATED_BODY()
public:
	void Initialize();
	void Destroy();

	// Order Item
	void RenewItems(TMap<int32, int32> aTransferItems);


	// Staff
	void RenewStaff(int32 aStaffId);
	
private:
	// Order Item
	TMap<int32, int32> Items;

	// Staff
	TMap<int32, class UMS_StaffPropertyElementData*> StaffPropertys;
public:
	inline static TObjectPtr<UMS_TestServer> TestServer = nullptr;
	static UMS_TestServer* GetInstance();
	
#define gTestServer (*UMS_TestServer::GetInstance())
};
