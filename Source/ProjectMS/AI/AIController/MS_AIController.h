#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Utility/MS_Define.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MS_AIController.generated.h"

UCLASS() class PROJECTMS_API AMS_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMS_AIController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aInPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type aEndPlayReason) override;

	UFUNCTION(BlueprintCallable) virtual void ExecuteBehaviorTree();
	UFUNCTION(BlueprintCallable) virtual void TerminateBehaviorTree();
	UFUNCTION() virtual void SynchronizeBlackboard();

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UBlackboardComponent* BlackboardComponent = nullptr;

	// Instance
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UBehaviorTree* DefaultBehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UBlackboardData* BlackboardData = nullptr;
};
