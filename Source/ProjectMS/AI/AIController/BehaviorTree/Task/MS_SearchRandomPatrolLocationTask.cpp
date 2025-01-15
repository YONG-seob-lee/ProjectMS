#include "AI/AIController/BehaviorTree/Task/MS_SearchRandomPatrolLocationTask.h"

#include "AI/AIController/MS_AIController.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "NavigationSystem.h"

UMS_SearchRandomPatrolLocationTask::UMS_SearchRandomPatrolLocationTask()
{
	NodeName = TEXT("Random Patrol");
}

EBTNodeResult::Type UMS_SearchRandomPatrolLocationTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	AMS_AICharacter* OwnerCharacter = Cast<AMS_AICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	AMS_AIController* OwnerController = Cast<AMS_AIController>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerController"))));

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation RandomLocation = {};

	if (NavigationSystem->GetRandomReachablePointInRadius(OwnerCharacter->GetActorLocation(), PatrolRadius, RandomLocation) == true)
	{
		aOwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandomPatrolLocation")), RandomLocation.Location);
	}

	return Result;
}
