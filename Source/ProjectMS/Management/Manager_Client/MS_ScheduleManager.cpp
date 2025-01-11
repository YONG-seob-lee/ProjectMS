// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleManager.h"

#include "MS_Define.h"

void FMS_TimeSchedule::SetScheduleType(EMS_ScheduleType aType)
{
	switch(aType)
	{
	case EMS_ScheduleType::Prepare:
		{
			if(ScheduleType != EMS_ScheduleType::Deadline)
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			
			PassTheDay();
			Minute = 420;
			break;
		}
	case EMS_ScheduleType::UpAndDown:
		{
			if(ScheduleType != static_cast<EMS_ScheduleType>(static_cast<int32>(aType) - 1))
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			Minute = 420;
			break;
		}
	case EMS_ScheduleType::OpenMarket:
		{
			if(ScheduleType != static_cast<EMS_ScheduleType>(static_cast<int32>(aType) - 1))
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			Minute = 540;
			break;
		}
	case EMS_ScheduleType::Deadline:
		{
			if(ScheduleType != static_cast<EMS_ScheduleType>(static_cast<int32>(aType) - 1))
			{
				MS_LOG(TEXT("Miss Schedule! "));
				return;
			}
			Minute = 1200;
			break;
		}
	default:
		{
			break;
		}
	}
	
	ScheduleType = aType;
}

EMS_ScheduleType FMS_TimeSchedule::GetNextScheduleType()
{
	switch(ScheduleType)
	{
	case EMS_ScheduleType::Deadline:
		{
			return EMS_ScheduleType::Prepare;
		}
	default:
		{
			return static_cast<EMS_ScheduleType>(static_cast<int32>(ScheduleType) + 1);
		}
	}
}

void FMS_TimeSchedule::PassTheDay()
{
	Day += 1;
	if(Day > 28)
	{
		Month +=1;
		Day = 1;
		if(Month > 12)
		{
			Year +=1;
			Month = 1;
		}
	}
}

void FMS_TestServerScheduler::RenewSchedule(EMS_ScheduleType aType)
{
	CurrentTime.SetScheduleType(aType);

	if(Manager)
	{
		// "TEST" Step.4 : 서버에서 클라로 전송.
		Manager->TakeTimeSchedule(&CurrentTime);
	}
}

UMS_ScheduleManager::UMS_ScheduleManager()
{
	ScheduleManager = this;
}

void UMS_ScheduleManager::BuiltInInitialize()
{
	Super::BuiltInInitialize();
}

void UMS_ScheduleManager::Initialize()
{
	Super::Initialize();

	// "TEST" Step.1 : 최초로 서버에서 스케쥴 데이터를 받음.
	TakeTimeSchedule(nullptr);
}

void UMS_ScheduleManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_ScheduleManager::PreFinalize()
{
	Super::PreFinalize();
}

void UMS_ScheduleManager::Finalize()
{
	delete TimeSchedule;
	Super::Finalize();
}

void UMS_ScheduleManager::BuiltInFinalize()
{
	Super::BuiltInFinalize();
}

void UMS_ScheduleManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ScheduleManager::TakeTimeSchedule(FMS_TimeSchedule* aTimeSchedule)
{
	// 나중에는 서버에서 전달받음.
	//TimeSchedule = aTimeSchedule;

	// 테스트용 데이터 생성.
	if(TimeSchedule == nullptr)
	{
		TimeSchedule = new FMS_TimeSchedule(2025, 1, 1 , 390, EMS_ScheduleType::Prepare);
	}

	switch(TimeSchedule->GetCurrentScheduleType())
	{
	case EMS_ScheduleType::UpAndDown:
		{
			// 타이머를 매니저에서 돌려 (게임시간 1분당 현실시간 0.5초)
			PlayTimer(120);
		}
	case EMS_ScheduleType::OpenMarket:
		{
			PlayTimer(660);
		}
	case EMS_ScheduleType::Prepare:
	case EMS_ScheduleType::Deadline:
		{
			// 타이머 없어도 돼
		}
	default:
		{
			break;
		}
	}
	
}

void UMS_ScheduleManager::TransferServer()
{
	TestServer.RenewSchedule(TimeSchedule->GetNextScheduleType());
}

void UMS_ScheduleManager::PlayTimer(int32 aGamePlayMinute)
{
	const float RealTimeSecond = static_cast<float>(aGamePlayMinute) / 2;
	MS_LOG(TEXT("====== UMS_ScheduleManager::PlayTimer \' In Rate Time : %f \'"), RealTimeSecond);
	
	GetWorld()->GetTimerManager().SetTimer(MarketPlayTimerHandle, this, &UMS_ScheduleManager::EndTimer, RealTimeSecond, false);
}

void UMS_ScheduleManager::EndTimer()
{
	// "TEST" Step.3 게임플레이가 끝나면 서버로 보냄. 
	TransferServer();
}

UMS_ScheduleManager* UMS_ScheduleManager::GetInstance()
{
	return ScheduleManager; 
}
