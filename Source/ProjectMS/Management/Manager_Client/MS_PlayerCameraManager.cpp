#include "Management/Manager_Client/MS_PlayerCameraManager.h"

#include "Camera/CameraModifier_CameraShake.h"
#include "Kismet/GameplayStatics.h"

#include "CoreClass/Controller/MS_PlayerController.h"

#include "Camera/ViewCamera/QuarterViewCamera/MS_QuarterViewCamera.h"
#include "Camera/ViewCamera/SideViewCamera/MS_SideViewCamera.h"

#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"
#include "Camera/CameraMode/FollowingPlayerCameraMode/MS_FollowingPlayerCameraMode.h"
#include "Camera/CameraMode/ImmobileCameraMode/MS_ImmobileCameraMode.h"

#include "Camera/CameraEffect/MS_CameraEffect.h"
#include "Camera/CameraEffect/CameraShake/MS_CameraShake.h"

namespace ViewCamera
{
	const FName Quarter = TEXT("QuarterViewCamera");
	const FName Side = TEXT("SideViewCamera");
}

AMS_PlayerCameraManager::AMS_PlayerCameraManager()
{
	CameraManager = this;
	CameraModeMap.Add(EMS_CameraModeType::FollowingInputCameraMode, CreateDefaultSubobject<UMS_FollowingInputCameraMode>(TEXT("FollowingInputCameraMode")));
	CameraModeMap.Add(EMS_CameraModeType::FollowingPlayerCameraMode, CreateDefaultSubobject<UMS_FollowingPlayerCameraMode>(TEXT("FollowingPlayerCameraMode")));
	CameraModeMap.Add(EMS_CameraModeType::ImmobileCameraMode, CreateDefaultSubobject<UMS_ImmobileCameraMode>(TEXT("ImmobileCameraMode")));

	CameraEffect = CreateDefaultSubobject<UMS_CameraEffect>(TEXT("CameraEffect"));
}

void AMS_PlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	InitializeViewCamera();

	SwitchViewCamera(EMS_ViewCameraType::QuarterView);
	SwitchCameraMode(EMS_CameraModeType::FollowingInputCameraMode);

	AdjustPostProcessEffect(CameraEffect->GetCameraPostProcessEffect());
}

void AMS_PlayerCameraManager::Destroyed()
{
	Super::Destroyed();
}

void AMS_PlayerCameraManager::FadeInCamera(float aDuration, EMS_InterpolationType aInterpolationType)
{
}

void AMS_PlayerCameraManager::FadeOutCamera(float aDuration, EMS_InterpolationType aInterpolationType)
{
}

void AMS_PlayerCameraManager::ZoomCamera(float aDistance)
{
	float TargetCameraDistance = ViewCamera.Get()->CameraDistance + (-aDistance * CAMERA_DISTANCE_STRANGTH);
	TargetCameraDistance = FMath::Clamp(TargetCameraDistance, MIN_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);

	const float NewInertiaForce = FMath::Clamp((TargetCameraDistance - ViewCamera.Get()->CameraDistance) * 0.9f, -100.0f, 100.0f);

	if (GetWorld()->GetTimerManager().IsTimerActive(CameraInertiaTimerHandle))
	{
		CameraInertiaForce = NewInertiaForce;
		return;
	}

	CameraInertiaForce = NewInertiaForce;

	GetWorld()->GetTimerManager().SetTimer(CameraInertiaTimerHandle, [this]()
		{
			CameraInertiaForce *= 0.9f;

			if (FMath::Abs(CameraInertiaForce) < 0.01f)
			{
				CameraInertiaForce = 0.0f;
				GetWorld()->GetTimerManager().ClearTimer(CameraInertiaTimerHandle);
				return;
			}

			float NewCameraDistance = ViewCamera.Get()->CameraDistance + CameraInertiaForce;
			NewCameraDistance = FMath::Clamp(NewCameraDistance, MIN_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);

			ViewCamera.Get()->AdjustCameraDistance(NewCameraDistance);

		}, 0.01f, true);
}

void AMS_PlayerCameraManager::OrbitCamera(float aFloat)
{
}

FRotator AMS_PlayerCameraManager::GenerateInertiaForceForRotation(FRotator aCurrentRotation, FRotator aTargetRotation, float& aVelocity, float aDampingFactor)
{
	FRotator Delta = aTargetRotation - aCurrentRotation;
	aVelocity += Delta.Yaw * aDampingFactor;
	aVelocity *= aDampingFactor;

	return aCurrentRotation + FRotator(0.0f, aVelocity, 0.0f);
}

void AMS_PlayerCameraManager::DEBUGINPUT_OrbitCamera(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend)
{
	TargetCameraRotation = ViewCamera.Get()->GetActorRotation();
	TargetCameraRotation.Yaw += aPointerGlidePositionDelta.X * 0.9f;

	if (!GetWorld()->GetTimerManager().IsTimerActive(CameraRotationTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(CameraRotationTimerHandle, [this]()
			{
				FRotator CurrentRotation = ViewCamera.Get()->GetActorRotation();

				static float VelocityYaw = 0.0f;

				FRotator NewRotation = GenerateInertiaForceForRotation(CurrentRotation, TargetCameraRotation, VelocityYaw, 0.2f);
				NewRotation.Yaw = FMath::Clamp(NewRotation.Yaw, -45.0f, 45.0f);

				ViewCamera.Get()->SetActorRotation(NewRotation);

				if (FMath::Abs(VelocityYaw) < 0.01f && FMath::IsNearlyEqual(NewRotation.Yaw, TargetCameraRotation.Yaw, 0.01f))
				{
					GetWorld()->GetTimerManager().ClearTimer(CameraRotationTimerHandle);
				}
			}, 0.005f, true);
	}
}
void AMS_PlayerCameraManager::ShakeCamera(float aIntensity, float aDuration)
{
	FAddCameraShakeParams AddCameraShakeParams = {};
	AddCameraShakeParams.Scale = aIntensity;
	AddCameraShakeParams.DurationOverride = aDuration;

	StartCameraShake(UMS_CameraShake::StaticClass(), AddCameraShakeParams);
}

void AMS_PlayerCameraManager::InitializeViewCamera()
{
	FActorSpawnParameters ActorSpawnParameters = {};
	
	ActorSpawnParameters.Name = ViewCamera::Quarter;
	ViewCameraMap.Add(EMS_ViewCameraType::QuarterView, GetWorld()->SpawnActor<AMS_QuarterViewCamera>(AMS_QuarterViewCamera::StaticClass(), FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector), ActorSpawnParameters));

	ActorSpawnParameters.Name = ViewCamera::Side;
	ViewCameraMap.Add(EMS_ViewCameraType::SideView, GetWorld()->SpawnActor<AMS_SideViewCamera>(AMS_SideViewCamera::StaticClass(), FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector), ActorSpawnParameters));

	for (const TPair<EMS_ViewCameraType, TObjectPtr<AMS_ViewCamera>>& PairMap : ViewCameraMap)
	{
		PairMap.Value->Deactivate();
	}
}

void AMS_PlayerCameraManager::SwitchViewCamera(EMS_ViewCameraType aViewCameraType, FViewTargetTransitionParams aTransitionParam /* = FViewTargetTransitionParams() */)
{
	TObjectPtr<AMS_ViewCamera> TempViewCamera = ViewCameraMap.Find(aViewCameraType)->Get();

	if (TempViewCamera == nullptr)
	{
		MS_CHECK(TempViewCamera);
		return;
	}

	if (ViewCameraType == aViewCameraType)
	{
		return;
	}

	if (ViewCamera.IsValid() == true)
	{
		ViewCamera->Deactivate();
	}

	ViewCamera = TempViewCamera;
	ViewCameraType = aViewCameraType;

	if(aTransitionParam.BlendTime > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(CameraTransitionTimerHandle, [this]()
		{
			if(OnFinishedCameraTransition.IsBound())
			{
				OnFinishedCameraTransition.Execute();
				OnFinishedCameraTransition.Unbind();
			}
		}, aTransitionParam.BlendTime, false);
		
	}
	
	SetViewTarget(ViewCamera.Get(), aTransitionParam);
}

void AMS_PlayerCameraManager::SwitchCameraMode(EMS_CameraModeType aCameraModeType)
{
	UMS_CameraMode* TempCameraMode = CameraModeMap.Find(aCameraModeType)->Get();

	if (TempCameraMode == nullptr || CameraMode == TempCameraMode)
	{
		return;
	}

	if (CameraMode.IsValid() == true)
	{
		CameraMode->DeactivateMode();
	}

	CameraMode = TempCameraMode;
	CameraMode->Bind(this);
	CameraMode->ActivateMode();
}

void AMS_PlayerCameraManager::AdjustPostProcessEffect(UMS_CameraPostProcessEffect* aCameraPostProcessEffect)
{
	MS_CHECK(ViewCamera.Get()); MS_CHECK(aCameraPostProcessEffect);

	ViewCamera->AdjustPostProcessEffect(aCameraPostProcessEffect);
}

void AMS_PlayerCameraManager::LocateAndRotateCamera(const FVector& aLocation, const FRotator& aRotation, EMS_ViewCameraType aViewCameraType)
{
	if(const TObjectPtr<class AMS_ViewCamera>* TargetViewCamera = ViewCameraMap.Find(aViewCameraType))
	{
		(*TargetViewCamera)->SetActorLocationAndRotation(aLocation, aRotation);
	}
}

void AMS_PlayerCameraManager::LocateCamera(FVector aLocation)
{
	
	ViewCamera->SetActorLocation(aLocation);
}

void AMS_PlayerCameraManager::RotateCamera(FRotator aRotation)
{
	ViewCamera->SetActorRotation(aRotation);
}

void AMS_PlayerCameraManager::DollyIn(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldOffset(FVector(1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::DollyOut(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldOffset(FVector(-1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::TruckLeft(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldOffset(FVector(0.0f, -1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::TruckRight(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldOffset(FVector(0.0f, 1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::DollyAndTruck(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend)
{
	ViewCamera->AddActorWorldOffset(FVector(aPointerGlidePositionDeltaTrend.Y, -aPointerGlidePositionDeltaTrend.X, 0.0f) * MoveSensitivity);
	GenerateInertiaForce(FVector(aPointerGlidePositionDeltaTrend.Y, -aPointerGlidePositionDeltaTrend.X, 0.0f) * 0.85f);
}

void AMS_PlayerCameraManager::PedestalUp(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldOffset(FVector(0.0f, 0.0f, 1.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::PedestalDown(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldOffset(FVector(0.0f, 0.0f, -1.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::RollCounterclockwise(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldRotation(FRotator(0.0f, 0.0f, -1.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::RollClockwise(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldRotation(FRotator(0.0f, 0.0f, 1.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::TiltUp(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldRotation(FRotator(1.0f, 0.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::TiltDown(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldRotation(FRotator(-1.0f, 0.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::PanLeft(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldRotation(FRotator(0.0f, -1.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::PanRight(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		ViewCamera->AddActorWorldRotation(FRotator(0.0f, 1.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}

void AMS_PlayerCameraManager::GenerateInertiaForce(FVector aMagnitude)
{
	InertiaForceMagnitude += aMagnitude;

	if (!GetWorld()->GetTimerManager().IsTimerActive(GenerateInertiaForceTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(GenerateInertiaForceTimerHandle, [&]()
			{
				FVector AppliedInertiaForceMagnitude = InertiaForceMagnitude * 0.025f;
				InertiaForceMagnitude -= AppliedInertiaForceMagnitude;

				FVector NewCameraLocation = ViewCamera->GetActorLocation() + AppliedInertiaForceMagnitude;
				ViewCamera->SetActorLocation(NewCameraLocation);

				if (InertiaForceMagnitude.Equals(FVector::ZeroVector, 0.001f))
				{
					GetWorld()->GetTimerManager().ClearTimer(GenerateInertiaForceTimerHandle);
					InertiaForceMagnitude = FVector::ZeroVector;
				}
			}, 0.005f, true);
	}
}

AMS_PlayerCameraManager* AMS_PlayerCameraManager::GetInstance()
{
	return CameraManager;
}
