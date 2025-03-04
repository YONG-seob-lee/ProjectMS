// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/MS_BTDecorator.h"
#include "MS_CustomerShoppingLoopBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerShoppingLoopBTDecorator : public UMS_BTDecorator
{
	GENERATED_BODY()
public:
	UMS_CustomerShoppingLoopBTDecorator(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	virtual FString GetStaticDescription() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual uint16 GetInstanceMemorySize() const override;
	
	UPROPERTY(Category=Decorator, BlueprintReadOnly);
	int32 ShoppingNumLoops = 3;

private:
	int32 CurrentRemainLoops = 0;
};
