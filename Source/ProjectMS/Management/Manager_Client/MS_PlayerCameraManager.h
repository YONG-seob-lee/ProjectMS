#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "InputActionValue.h"
#include "MS_PlayerCameraManager.generated.h"

UENUM() enum class EMS_ViewCameraType
{
	Undefined,
	QuarterView,
	SideView,
	TopView
};

UENUM() enum class EMS_CameraModeType
{
	Undefined,
	FollowingInputCameraMode,
	FollowingPlayerCameraMode,
	ImmobileCameraMode
};

UCLASS() class PROJECTMS_API AMS_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	AMS_PlayerCameraManager();

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	void InitializeViewCamera();
	void FinalizeViewCamera();

	void SwitchViewCamera(EMS_ViewCameraType aViewCameraType, FViewTargetTransitionParams aTransitionParam = FViewTargetTransitionParams());
	void SwitchCameraMode(EMS_CameraModeType aCameraModeType);

	void AdjustPostProcessEffect(class UMS_CameraPostProcessEffect* aCameraPostProcessEffect) const;
	
	FORCEINLINE void RestrictCameraMovement(bool aFlag) { bRestrictCameraFlag = aFlag; }
	FORCEINLINE bool GetIsRestrictCameraMovement() const { return bRestrictCameraFlag; }
	FORCEINLINE FSimpleDelegate& GetOnFinishedCameraTransitionDelegate() { return OnFinishedCameraTransition; }
	FORCEINLINE TWeakObjectPtr<class AMS_ViewCamera> GetCurrentCamera() const { return CurrentCamera; }

	UFUNCTION(BlueprintCallable) void ZoomCamera(float aDistance);
	UFUNCTION(BlueprintCallable) void OrbitCamera(float aFloat);
	UFUNCTION(BlueprintCallable) void ShakeCamera(float aIntensity, float aDuration);

	void LocateCamera(const FVector& aLocation, EMS_ViewCameraType aViewCameraType = EMS_ViewCameraType::QuarterView);
	
	void LocateCamera(const FVector& aLocation) const;
	void RotateCamera(const FRotator& aRotation) const;

	UFUNCTION() void DollyIn(const FInputActionValue& aValue);
	UFUNCTION() void DollyOut(const FInputActionValue& aValue);
	UFUNCTION() void TruckLeft(const FInputActionValue& aValue);
	UFUNCTION() void TruckRight(const FInputActionValue& aValue);
	UFUNCTION() void DollyAndTruck(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend);
	UFUNCTION() void PedestalUp(const FInputActionValue& aValue);
	UFUNCTION() void PedestalDown(const FInputActionValue& aValue);
	UFUNCTION() void RollCounterclockwise(const FInputActionValue& aValue);
	UFUNCTION() void RollClockwise(const FInputActionValue& aValue);
	UFUNCTION() void TiltUp(const FInputActionValue& aValue);
	UFUNCTION() void TiltDown(const FInputActionValue& aValue);
	UFUNCTION() void PanLeft(const FInputActionValue& aValue);
	UFUNCTION() void PanRight(const FInputActionValue& aValue);

	UFUNCTION() void DEBUG_INPUT_OrbitCamera(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend);
	
private:
	void GenerateInertiaForce(const FVector& aMagnitude);
	FRotator GenerateInertiaForceForRotation(const FRotator& aCurrentRotation, const FRotator& aTargetRotation, float& aVelocity, float aDampingFactor);
	
	EMS_ViewCameraType ViewCameraType = EMS_ViewCameraType::Undefined;
	bool bRestrictCameraFlag = false;

	float MoveSensitivity = 1.f;
	float MoveDensity = 1.f;
	float TurnSensitivity = 1.f;
	FTimerHandle GenerateInertiaForceTimerHandle = {};
	FVector InertiaForceMagnitude = {};

	float CameraInertiaForce = 0.f;
	FTimerHandle CameraInertiaTimerHandle = {};

	FTimerHandle CameraTransitionTimerHandle = {};
	FSimpleDelegate OnFinishedCameraTransition = {};
	
	// DEBUG
	FTimerHandle CameraRotationTimerHandle = {};
	FRotator TargetCameraRotation = {};
	
	TWeakObjectPtr<class AMS_ViewCamera> CurrentCamera = nullptr;
	TWeakObjectPtr<class UMS_CameraMode> CurrentCameraMode = nullptr;
	TObjectPtr<class UMS_CameraEffect> CameraEffect = nullptr;

	TMap<EMS_CameraModeType, TObjectPtr<class UMS_CameraMode>> CameraModeMap = {};
	TMap<EMS_ViewCameraType, TObjectPtr<class AMS_ViewCamera>> ViewCameraMap = {};

public:
	inline static TObjectPtr<AMS_PlayerCameraManager> CameraManager = nullptr;
	static AMS_PlayerCameraManager* GetInstance();
	
#define gCameraMng (*AMS_PlayerCameraManager::GetInstance())
};