// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_PointerData.h"

#include "Framework/Application/IInputProcessor.h"

UENUM()
enum class EMS_TouchActionType : uint8
{
	None = 0,
	Down,
	Up,
	Double,
};
/**
 * 
 */
class PROJECTMS_API IMS_TouchInputProcessor : public IInputProcessor, public FGCObject
{
public:
	void Initialize();
	void Finalize();

	virtual void AddReferencedObjects(FReferenceCollector& aCollector) override;
	virtual FString GetReferencerName() const override;
	virtual void Tick(const float aDeltaTime, FSlateApplication& aSlateApp, TSharedRef<ICursor> aCursor) override;
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent) override;
	virtual bool HandleMouseMoveEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent) override;
	virtual bool HandleMouseButtonUpEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent) override;
	virtual bool HandleMouseButtonDoubleClickEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent) override;

	// Hold, LongTouch, Click, Glide, Pinch 등의 액션은 Data 구조체 내에서 관리.
	void HandleRotate();

	bool IsPointerPressed() const;

	
private:
	FMS_PointerData* CreatePointer(const FPointerEvent& aMouseEvent);
	void DestroyPointer(FMS_PointerData* aPointerData);
	FMS_PointerData* GetPointerData(uint32 aPointerIndex);
	
	void ShootLineTrace(const FVector2D& aPointerDownPosition, EMS_TouchActionType aType);

	int32 FingerCount = 0;

	TMap<int32, FMS_PointerData*> PointerDatas;
	
	TQueue<int32> TouchEffectQueue;
};
