﻿#pragma once

namespace IntervalTimeValue
{
	constexpr double Separation = 10000000.f;
};

namespace PointerParameter
{
	constexpr int32 ArrayFirst = 0;
	constexpr int32 MoveDeltaArrayMax = 5;
	const FVector2D DefaultVector = FVector2D(-FLT_MAX, -FLT_MAX);
}

struct FMS_PointerData
{
public:
	FMS_PointerData();
	~FMS_PointerData();

	void Initialize();
	void Finalize();

	void Tick(const float aDeltaTime);

	FORCEINLINE void SetPointerIndex(uint32 aPointerIndex) { PointerIndex = aPointerIndex; }
	FORCEINLINE uint32 GetPointerIndex() const { return PointerIndex; }
	
	FORCEINLINE void SetPointerPressFlag(bool bIsPressed) { IsPointerPressFlag = bIsPressed; }
	FORCEINLINE bool IsPointerPressed() const { return IsPointerPressFlag; }
	
	FORCEINLINE void SetMouseRightButtonPressFlag(bool bIsRightPressed) { IsMouseRightButtonPressFlag = bIsRightPressed; }
	
	FORCEINLINE void SetPointerDownTimestamp(int64 aPointerDownTimestamp) { PointerDownTimestamp = aPointerDownTimestamp; }
	FORCEINLINE void SetPointerDownPosition(const FVector2D& aPointerDownPosition) { PointerDownPosition = aPointerDownPosition; }
	FORCEINLINE FVector2D GetPointerDownPosition() const { return PointerDownPosition; }

	FORCEINLINE void SetPointerUpTimestamp(int64 aPointerUpTimestamp) { PointerUpTimestamp = aPointerUpTimestamp; }
	FORCEINLINE void SetPointerUpPosition(const FVector2D& aPointerUpPosition) { PointerUpPosition = aPointerUpPosition; }
	FORCEINLINE FVector2D GetPointerUpPosition() const { return PointerUpPosition; }

	FORCEINLINE void ResetElapsedHoldTime() { ElapsedHoldTime = 0.f; }
	void CalculateIntervalTime();

	void HandlePointerHold();
	void HandlePointerLongTouch() const;
	void HandlePointerClick(const FVector2D& AbsoluteScreenPosition);
	void HandlePointerGlide();
	void HandlePinchAction();
	
	FORCEINLINE FVector2D GetPointerMovePosition() const { return PointerMovePosition; }
	void UpdatePointerMovePosition(const FVector2D& AbsoluteScreenPosition);

	void PlayParticle() const;

private:
	uint32 PointerIndex = -1;
	bool IsPointerPressFlag = false;
	bool IsMouseRightButtonPressFlag = false;
	
	int64 PointerDownTimestamp = 0;
	FVector2D PointerDownPosition = PointerParameter::DefaultVector;

	int64 PointerUpTimestamp = 0;
	FVector2D PointerUpPosition = PointerParameter::DefaultVector;

	float PointerDownUpIntervalTime = -FLT_MAX;

	int64 PointerClickTimestamp = 0;
	FVector2D PointerClickPosition = PointerParameter::DefaultVector;
	float PointerClickIntervalTime = -FLT_MAX;
	
	FVector2D PointerHoldPosition = PointerParameter::DefaultVector;

	FVector2D PointerMovePosition = PointerParameter::DefaultVector;
	FVector2D PointerMovePositionDelta = PointerParameter::DefaultVector;
	TArray<FVector2D> PointerMovePositionDeltaArray = {};
	FVector2D PointerMovePositionDeltaTrend = PointerParameter::DefaultVector;
	
	FVector2D PointerGlidePosition = PointerParameter::DefaultVector;
	FVector2D PointerGlidePositionDelta = PointerParameter::DefaultVector;
	TArray<FVector2D> PointerGlidePositionDeltaArray = {};
	FVector2D PointerGlidePositionDeltaTrend = PointerParameter::DefaultVector;
	
	float ElapsedHoldTime = 0.f;
	float ElapsedHoldTimeInternal = 0.f;
	// Fixed Value
	float PointerHoldDelay = 0.f;
	float PointerLongTouch = 0.f;
	float PointerClickDelay = 0.f;
};