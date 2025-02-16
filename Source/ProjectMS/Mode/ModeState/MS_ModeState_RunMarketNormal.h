// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeState_RunMarket.h"
#include "MS_ModeState_RunMarketNormal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeState_RunMarketNormal : public UMS_ModeState_RunMarket
{
	GENERATED_BODY()

public:
	UMS_ModeState_RunMarketNormal();
	
	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual void Begin() override;
	virtual void Exit() override;
	
	virtual void UpdateMinute(int32 aCurrentMinute) override;
	virtual void UpdateScheduleEvent(int32 aScheduleEvent) override;

public:
	virtual void OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;

	virtual void OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult) override;

	virtual void OnInputPointerLongTouch(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult) override;

	virtual void OnInputPointerDoubleClickEvent(FVector2D aPosition, const FHitResult& aInteractableHitResult) override;

	virtual void OnPinchAction(float aPinchValue) override;

	
	// Select
	void SelectActor(AActor* aSelectedActor);
	void UnselectActor();
	
	UFUNCTION()
	void OnSelectActor(AActor* aSelectedActor);	// 기존의 것과 다른 Prop이 선택되야 호출됨

	UFUNCTION()
	void OnUnselectActor(AActor* aUnselectedActor);
};
