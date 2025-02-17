// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_AITask.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AITask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UMS_AITask(const FObjectInitializer& ObjectInitializer);

	// Note 용섭 : 계속 실패중이다가 성공이 뜨면 '셀렉터' 또는 '시퀸서' 가 다음 임무를 수행한다.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Note 용섭 : 테스트 중간에 캔슬이 됐을 때의 행동 함수.
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Note 용섭 : 테스크 중의 행동 함수.
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

protected:
	float GetRandomRemainTime(float MinTime = 2.f, float MaxTime = 10.f);
};
