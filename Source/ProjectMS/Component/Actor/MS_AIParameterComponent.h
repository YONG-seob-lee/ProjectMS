// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "Components/ActorComponent.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "MS_AIParameterComponent.generated.h"

UENUM()
enum class EMS_ChattingType
{
	Undefined = 0,
	ComeInMarket, // 마켓 진입
	PriceTooExpensive,
	PriceResonable,
	PriceCheap,
	Hungry,
	Thirsty,
	NuclearMissile,
	ExitOutMarket // 마켓 나감
};

namespace ChattingLocalizedString
{
	const FString ComeInMarket = TEXT("Customer_Comment_01");
	const FString ExitOutMarket = TEXT("Customer_Comment_02");
	const FString PriceTooExpansive = TEXT("Customer_Comment_03");
	const FString PriceResonable = TEXT("Customer_Comment_04");
	const FString PriceCheap = TEXT("Customer_Comment_05");
	const FString Hungry = TEXT("Customer_Comment_06");
	const FString Thirsty = TEXT("Customer_Comment_07");
	const FString NuclearMissile = TEXT("Customer_Comment_08");
}

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_AIParameterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMS_AIParameterComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;

	template <typename T>
	void ChattingTrigger(EMS_ChattingType aChattingType, T aParameter01, T aParameter02)
	{
		switch (aChattingType)
		{
		case EMS_ChattingType::ComeInMarket:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::ComeInMarket), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		case EMS_ChattingType::ExitOutMarket:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::ComeInMarket), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, false, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		case EMS_ChattingType::PriceTooExpensive:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::PriceTooExpansive), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, false, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		case EMS_ChattingType::PriceResonable:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::PriceResonable), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, false, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		case EMS_ChattingType::PriceCheap:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::PriceCheap), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, false, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		case EMS_ChattingType::Hungry:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::Hungry), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, false, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		case EMS_ChattingType::Thirsty:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::Thirsty), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, false, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		case EMS_ChattingType::NuclearMissile:
			{
				const FText Chatting = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, ChattingLocalizedString::NuclearMissile), {aParameter01});
				gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, false, gScheduleMng.GetCurrentMinute(), Chatting));
				break;
			}
		default:
			{
				break;
			}
		}
	}

	void PurchaseTrigger(int32 aItemId, int32 aItemCount) const;
	
private:
	MS_Handle UnitHandle = INDEX_NONE;
};
