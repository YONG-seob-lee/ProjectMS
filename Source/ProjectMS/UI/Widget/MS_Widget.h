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
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bActivate = true);
	virtual void FinishWidget();
	
	virtual void NativeTick(const FGeometry& aMyGeometry, float aInDeltaTime) override;
	
	UFUNCTION()
	virtual void OnRuntimeInitialize();

	virtual void Active(bool bActive = true);

	FORCEINLINE FMS_ResourceWidgetInfo GetResourceWidgetInfo() const { return ResourceWidgetInfo; }
	FORCEINLINE void SetResourceWidgetInfo(const FMS_ResourceWidgetInfo& Info) { ResourceWidgetInfo = Info; }
	FORCEINLINE FVector2D GetCutoutFrameSize() const { return CutoutFrameSize; }
	FORCEINLINE FVector2D GetContentFrameSize() const { return ContentFrameSize; }
	void FillDefaultAnimations();

	TObjectPtr<UWidgetAnimation> GetAnimationByName(FName aAnimName) const;
	void PlayAnimationByName(FName aName, float aStartTime = 0.f, int32 aLoopCount = 1, EUMGSequencePlayMode::Type aPlayType = EUMGSequencePlayMode::Forward, float aSpeed = 1.f);
	bool IsExistAnim(FName aAnimName) const;
	
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<class UMS_CanvasPanel> RootCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UMS_CanvasPanel> CutoutFrameCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<UMS_CanvasPanel> ContentFrameCanvasPanel = nullptr;
	
private:
	bool IsManaged = false;
	FVector2D CutoutFrameSize = {};
	FVector2D ContentFrameSize = {};
	
	FMS_ResourceWidgetInfo ResourceWidgetInfo;
	
	UPROPERTY()
	TMap<FName, TObjectPtr<UWidgetAnimation>> WidgetAnimations;

};
