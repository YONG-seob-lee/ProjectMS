// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TestServer.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_StaffPropertyElementData.h"


void UMS_TestServer::Initialize()
{
	TestServer = this;
}

void UMS_TestServer::Destroy()
{
}

void UMS_TestServer::RenewItems(TMap<int32, int32> aTransferItems)
{
	for(const auto& TransferItem : aTransferItems)
	{
		if(int32* TargetItem = Items.Find(TransferItem.Key))
		{
			*TargetItem += TransferItem.Value; 
		}
		else
		{
			Items.Emplace(TransferItem.Key, TransferItem.Value);
		}
	}
	
	// "TEST" Step.4 : 서버에서 클라로 전송.
	gItemMng.SetItems(&Items);
}

void UMS_TestServer::RenewStaff(int32 aStaffId)
{
	if(UMS_StaffPropertyElementData* StaffProperty = MS_NewObject<UMS_StaffPropertyElementData>())
	{
		StaffPropertys.Emplace(aStaffId, StaffProperty);
		StaffProperty->SetStaffId(aStaffId);
		StaffProperty->SetHP(100);
		StaffProperty->SetCondition(100);
		StaffProperty->SetFeeling(1);
		StaffProperty->SetExpirationDate(5, 31);
	}
	gItemMng.SetStaffProperty(aStaffId, StaffPropertys[aStaffId]);
}

UMS_TestServer* UMS_TestServer::GetInstance()
{
	return TestServer;
}
