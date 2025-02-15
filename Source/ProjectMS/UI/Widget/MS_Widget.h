// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MS_Widget.generated.h"

namespace DefaultWidgetAnimation
{
	const FName Appearance = TEXT("Appearance");
	const FName DisAppearance = TEXT("DisAppearance");
	
	const FName Idle = TEXT("Idle");
}

struct FMS_ResourceWidgetInfo
{
	FMS_ResourceWidgetInfo(): zOrder(0), NotRender3D(false), bNotClosing(false), CreateTime(0) {}

	FString File;
	FName TypeName;
	int32 zOrder;
	bool NotRender3D;
	bool bNotClosing;
	float CreateTime;
	
	FORCEINLINE const FName& GetWidgetName() const { return TypeName; }
};

UENUM()
enum class EMS_TutorialDirection
{
	UpToRight = 1,
	DownToRight = 2,
	UpToLeft = 3,
	DownToLeft = 4
};

namespace Tutorial
{
	const FName SlotName = TEXT("TutorialSlot");
	const FVector2D DefaultSize = FVector2D(1000.f, 400.f);
}

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMS_Widget(const FObjectInitializer& aObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot = true);
	virtual void FinishWidget();
	
	virtual void NativeTick(const FGeometry& aMyGeometry, float aInDeltaTime) override;

	virtual void PlayTutorial(const FText& Desc, const FText& SubDesc);
	
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	
	UFUNCTION()
	virtual void OnRuntimeInitialize();

	virtual void Active(bool bActive = true, bool bAttachToRoot = true);

	FORCEINLINE FMS_ResourceWidgetInfo GetResourceWidgetInfo() const { return ResourceWidgetInfo; }
	FORCEINLINE void SetResourceWidgetInfo(const FMS_ResourceWidgetInfo& Info) { ResourceWidgetInfo = Info; }
	void FillDefaultAnimations();

	virtual void OnAnimFinished(const FName& aAnimName);

	TObjectPtr<UWidgetAnimation> GetAnimationByName(FName aAnimName) const;
	void PlayAnimationByName(FName aName, float aStartTime = 0.f, int32 aLoopCount = 1, EUMGSequencePlayMode::Type aPlayType = EUMGSequencePlayMode::Forward, float aSpeed = 1.f);
	void StopAnimationByName(FName aName);
	bool IsExistAnim(FName aAnimName) const;
	bool IsAnimationPlayingByName(const FName& aName) const;
	
private:
	bool IsManaged = false;
	
	TObjectPtr<class UNamedSlot> GetNamedSlot() const;
	void RePositionNamedSlot(const TObjectPtr<UPanelSlot>& NamedSlot) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "True"))
	EMS_TutorialDirection TutorialDirection = EMS_TutorialDirection::UpToRight;
	
	FMS_ResourceWidgetInfo ResourceWidgetInfo;
	
	UPROPERTY()
	TMap<FName, TObjectPtr<UWidgetAnimation>> WidgetAnimations;

};
