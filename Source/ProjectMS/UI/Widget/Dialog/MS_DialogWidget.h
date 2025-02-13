// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_DialogWidget.generated.h"

struct FMS_DialogParameter
{
public:
	FMS_DialogParameter() {}
	FMS_DialogParameter(const FString& aTypeText, float aTypeSpeed, TFunction<void()> aFunc);

	FORCEINLINE bool IsFinishType() const { return ProcessNumber >= TotalTypeNumber; }
	FString ShowType() const;
	FORCEINLINE void AddProcess() { ProcessNumber++; }
	FORCEINLINE float GetTypeSpeed() const { return TypeSpeed; }
	FORCEINLINE void FinishDialogEvent() const { if(DialogEndCallback){ DialogEndCallback(); } }

private:
	FString TypeText = FString();
	float TypeSpeed = 1.f;
	int32 TotalTypeNumber = 0;
	int32 ProcessNumber = 0;

	TFunction<void()> DialogEndCallback = nullptr;
};
/**
 * 
 */
namespace DialogAnimation
{
	const FName Start = TEXT("StartDialog");
	const FName Close = TEXT("CloseDialog");
}

UCLASS()
class PROJECTMS_API UMS_DialogWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Dialog"); }

	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;
	virtual void NativeConstruct() override;
	virtual void OnAnimFinished(const FName& aAnimName) override;

	void RequestDialog(const FMS_DialogParameter& aDialogParameter);

private:
	void ProcessTyping();
	void FinishedTyping();

	FMS_DialogParameter DialogParameter;
	FTimerHandle DialogTextTimerHandler;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DialogText = nullptr; 
};
