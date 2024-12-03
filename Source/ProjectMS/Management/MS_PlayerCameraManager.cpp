#include "Management/MS_PlayerCameraManager.h"

#include "Utility/MS_Define.h"
#include "Camera/CameraModifier_CameraShake.h"

#include "CoreClass/Controller/MS_PlayerController.h"

#include "Camera/ViewCamera/QuarterViewCamera/MS_QuarterViewCamera.h"

#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"
#include "Camera/CameraMode/FollowingPlayerCameraMode/MS_FollowingPlayerCameraMode.h"
#include "Camera/CameraMode/ImmobileCameraMode/MS_ImmobileCameraMode.h"

#include "Camera/CameraEffect/MS_CameraEffect.h"
#include "Camera/CameraEffect/CameraShake/MS_CameraShake.h"

AMS_PlayerCameraManager::AMS_PlayerCameraManager()
{
	CameraModeMap.Add(EMS_CameraModeType::FollowingInputCameraMode, CreateDefaultSubobject<UMS_FollowingInputCameraMode>(TEXT("FollowingInputCameraMode")));
	CameraModeMap.Add(EMS_CameraModeType::FollowingPlayerCameraMode, CreateDefaultSubobject<UMS_FollowingPlayerCameraMode>(TEXT("FollowingPlayerCameraMode")));
	CameraModeMap.Add(EMS_CameraModeType::ImmobileCameraMode, CreateDefaultSubobject<UMS_ImmobileCameraMode>(TEXT("ImmobileCameraMode")));

	CameraEffect = CreateDefaultSubobject<UMS_CameraEffect>(TEXT("CameraEffect"));
}

void AMS_PlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	SwitchViewCamera(EMS_ViewCameraType::QuarterView);
	SwitchCameraMode(EMS_CameraModeType::FollowingInputCameraMode);

	AdjustPostProcessEffect(CameraEffect->GetCameraPostProcessEffect());
}

void AMS_PlayerCameraManager::FadeInCamera(float aDuration, EMS_InterpolationType aInterpolationType)
{
}

void AMS_PlayerCameraManager::FadeOutCamera(float aDuration, EMS_InterpolationType aInterpolationType)
{
}

void AMS_PlayerCameraManager::ZoomCamera(float aMagnification, EMS_InterpolationType aInterpolationType)
{
	if (aInterpolationType == EMS_InterpolationType::Undefined)
	{
		MS_CHECK(true);
	}

	const float Duration = 0.5f;
	static float ElapsedTime;
	ElapsedTime = 0.0f;

	const float OriginZoomMagnification = ZoomMagnification;

	GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, [&, OriginZoomMagnification, aMagnification, aInterpolationType, Duration]()
		{
			float ProgressRate = ElapsedTime / Duration;
			ProgressRate = FMath::Clamp(ProgressRate, 0.0f, 1.0f);

			float InterpolatedRate = UMS_MathUtility::CalculateInterpolation(ProgressRate, aInterpolationType);
			float ChangedMagnification = FMath::Lerp(OriginZoomMagnification, aMagnification, InterpolatedRate);

			ViewCamera->AdjustCameraDistance(ViewCamera->CameraDistance * (1 / ChangedMagnification));
			ZoomMagnification = ChangedMagnification;

			if (ElapsedTime >= Duration)
			{
				GetWorld()->GetTimerManager().ClearTimer(ZoomTimerHandle);
				ElapsedTime = 0.0f;
			}
			else
			{
				ElapsedTime += 0.01f;
			}
		}, 0.01f, true);
}

void AMS_PlayerCameraManager::ShakeCamera(float aIntensity, float aDuration)
{
	FAddCameraShakeParams AddCameraShakeParams = {};
	AddCameraShakeParams.Scale = aIntensity;
	AddCameraShakeParams.DurationOverride = aDuration;

	StartCameraShake(UMS_CameraShake::StaticClass(), AddCameraShakeParams);
}

void AMS_PlayerCameraManager::SwitchViewCamera(EMS_ViewCameraType aViewCameraType)
{
	// TODO: Update
	if (ViewCameraType == aViewCameraType)
	{
		return;
	}

	TObjectPtr<AMS_QuarterViewCamera> TempViewCamera = nullptr;

	switch (aViewCameraType)
	{
	case EMS_ViewCameraType::Undefined:
	{
		break;
	}
	case EMS_ViewCameraType::QuarterView:
	{
		FActorSpawnParameters ActorSpawnParameters = {};
		ActorSpawnParameters.Name = TEXT("QuarterViewCamera");
		TempViewCamera = GetWorld()->SpawnActor<AMS_QuarterViewCamera>(AMS_QuarterViewCamera::StaticClass(), FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector), ActorSpawnParameters);
		break;
	}
	default:
	{
		break;
	}
	}

	MS_CHECK(TempViewCamera);

	if (ViewCamera != nullptr && ViewCamera->IsActorBeingDestroyed() == false)
	{
		ViewCamera->Destroy();
		ViewCamera = nullptr;
	}

	ViewCamera = TempViewCamera;
	ViewCameraType = aViewCameraType;

	SetViewTarget(ViewCamera);
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
	CameraMode->ActivateMode();
}

void AMS_PlayerCameraManager::AdjustPostProcessEffect(UMS_CameraPostProcessEffect* aCameraPostProcessEffect)
{
	MS_CHECK(ViewCamera); MS_CHECK(aCameraPostProcessEffect);

	ViewCamera->AdjustPostProcessEffect(aCameraPostProcessEffect);
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
		if (RestrictedZoneFlag == true)
		{
			FVector ExpectedMoveLocalLocation = RestrictedZoneTransform.InverseTransformPosition(ViewCamera->GetActorLocation() + FVector(1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
			if (FBox(-(RestrictedZoneSize / 2.0f), (RestrictedZoneSize / 2.0f)).IsInsideOrOn(ExpectedMoveLocalLocation) == false)
			{
				float ClosestLocalLocationXToZone = FMath::Clamp(ExpectedMoveLocalLocation.X, (-RestrictedZoneSize.X / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.X / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationYToZone = FMath::Clamp(ExpectedMoveLocalLocation.Y, (-RestrictedZoneSize.Y / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Y / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationZToZone = FMath::Clamp(ExpectedMoveLocalLocation.Z, (-RestrictedZoneSize.Z / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Z / 2.0f) - FLT_EPSILON);
				FVector ClosestWorldLocationToZone = RestrictedZoneTransform.TransformPosition(FVector(ClosestLocalLocationXToZone, ClosestLocalLocationYToZone, ClosestLocalLocationZToZone));
				ClosestWorldLocationToZone.Z = ViewCamera->GetActorLocation().Z;
				ViewCamera->SetActorLocation(ClosestWorldLocationToZone);
				return;
			}
		}

		ViewCamera->AddActorWorldOffset(FVector(1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::DollyOut(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		if (RestrictedZoneFlag == true)
		{
			FVector ExpectedMoveLocalLocation = RestrictedZoneTransform.InverseTransformPosition(ViewCamera->GetActorLocation() + FVector(-1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
			if (FBox(-(RestrictedZoneSize / 2.0f), (RestrictedZoneSize / 2.0f)).IsInsideOrOn(ExpectedMoveLocalLocation) == false)
			{
				float ClosestLocalLocationXToZone = FMath::Clamp(ExpectedMoveLocalLocation.X, (-RestrictedZoneSize.X / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.X / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationYToZone = FMath::Clamp(ExpectedMoveLocalLocation.Y, (-RestrictedZoneSize.Y / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Y / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationZToZone = FMath::Clamp(ExpectedMoveLocalLocation.Z, (-RestrictedZoneSize.Z / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Z / 2.0f) - FLT_EPSILON);
				FVector ClosestWorldLocationToZone = RestrictedZoneTransform.TransformPosition(FVector(ClosestLocalLocationXToZone, ClosestLocalLocationYToZone, ClosestLocalLocationZToZone));
				ClosestWorldLocationToZone.Z = ViewCamera->GetActorLocation().Z;
				ViewCamera->SetActorLocation(ClosestWorldLocationToZone);
				return;
			}
		}

		ViewCamera->AddActorWorldOffset(FVector(-1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::TruckLeft(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		if (RestrictedZoneFlag == true)
		{
			FVector ExpectedMoveLocalLocation = RestrictedZoneTransform.InverseTransformPosition(ViewCamera->GetActorLocation() + FVector(0.0f, -1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
			if (FBox(-(RestrictedZoneSize / 2.0f), (RestrictedZoneSize / 2.0f)).IsInsideOrOn(ExpectedMoveLocalLocation) == false)
			{
				float ClosestLocalLocationXToZone = FMath::Clamp(ExpectedMoveLocalLocation.X, (-RestrictedZoneSize.X / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.X / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationYToZone = FMath::Clamp(ExpectedMoveLocalLocation.Y, (-RestrictedZoneSize.Y / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Y / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationZToZone = FMath::Clamp(ExpectedMoveLocalLocation.Z, (-RestrictedZoneSize.Z / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Z / 2.0f) - FLT_EPSILON);
				FVector ClosestWorldLocationToZone = RestrictedZoneTransform.TransformPosition(FVector(ClosestLocalLocationXToZone, ClosestLocalLocationYToZone, ClosestLocalLocationZToZone));
				ClosestWorldLocationToZone.Z = ViewCamera->GetActorLocation().Z;
				ViewCamera->SetActorLocation(ClosestWorldLocationToZone);
				return;
			}
		}

		ViewCamera->AddActorWorldOffset(FVector(0.0f, -1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::TruckRight(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		if (RestrictedZoneFlag == true)
		{
			FVector ExpectedMoveLocalLocation = RestrictedZoneTransform.InverseTransformPosition(ViewCamera->GetActorLocation() + FVector(0.0f, 1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
			if (FBox(-(RestrictedZoneSize / 2.0f), (RestrictedZoneSize / 2.0f)).IsInsideOrOn(ExpectedMoveLocalLocation) == false)
			{
				float ClosestLocalLocationXToZone = FMath::Clamp(ExpectedMoveLocalLocation.X, (-RestrictedZoneSize.X / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.X / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationYToZone = FMath::Clamp(ExpectedMoveLocalLocation.Y, (-RestrictedZoneSize.Y / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Y / 2.0f) - FLT_EPSILON);
				float ClosestLocalLocationZToZone = FMath::Clamp(ExpectedMoveLocalLocation.Z, (-RestrictedZoneSize.Z / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Z / 2.0f) - FLT_EPSILON);
				FVector ClosestWorldLocationToZone = RestrictedZoneTransform.TransformPosition(FVector(ClosestLocalLocationXToZone, ClosestLocalLocationYToZone, ClosestLocalLocationZToZone));
				ClosestWorldLocationToZone.Z = ViewCamera->GetActorLocation().Z;
				ViewCamera->SetActorLocation(ClosestWorldLocationToZone);
				return;
			}
		}

		ViewCamera->AddActorWorldOffset(FVector(0.0f, 1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::DollyAndTruckOnMobile(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend)
{
	if (RestrictedZoneFlag == true)
	{
		FVector ExpectedMoveLocalLocation = RestrictedZoneTransform.InverseTransformPosition(ViewCamera->GetActorLocation() + FVector(aPointerGlidePositionDeltaTrend.Y, -aPointerGlidePositionDeltaTrend.X, 0.0f) * MoveSensitivity);
		if (FBox(-(RestrictedZoneSize / 2.0f), (RestrictedZoneSize / 2.0f)).IsInsideOrOn(ExpectedMoveLocalLocation) == false)
		{
			float ClosestLocalLocationXToZone = FMath::Clamp(ExpectedMoveLocalLocation.X, (-RestrictedZoneSize.X / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.X / 2.0f) - FLT_EPSILON);
			float ClosestLocalLocationYToZone = FMath::Clamp(ExpectedMoveLocalLocation.Y, (-RestrictedZoneSize.Y / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Y / 2.0f) - FLT_EPSILON);
			float ClosestLocalLocationZToZone = FMath::Clamp(ExpectedMoveLocalLocation.Z, (-RestrictedZoneSize.Z / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Z / 2.0f) - FLT_EPSILON);
			FVector ClosestWorldLocationToZone = RestrictedZoneTransform.TransformPosition(FVector(ClosestLocalLocationXToZone, ClosestLocalLocationYToZone, ClosestLocalLocationZToZone));
			ClosestWorldLocationToZone.Z = ViewCamera->GetActorLocation().Z;
			ViewCamera->SetActorLocation(ClosestWorldLocationToZone);
			return;
		}
	}

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

	if (GetWorld()->GetTimerManager().IsTimerActive(GenerateInertiaForceTimerHandle) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(GenerateInertiaForceTimerHandle, [&]()
			{
				FVector AppliedInertiaForceMagnitude = InertiaForceMagnitude * 0.025f;
				InertiaForceMagnitude -= AppliedInertiaForceMagnitude;

				FVector ExpectedMoveLocalLocation = RestrictedZoneTransform.InverseTransformPosition(ViewCamera->GetActorLocation() + AppliedInertiaForceMagnitude);
				if (FBox(-(RestrictedZoneSize / 2.0f), (RestrictedZoneSize / 2.0f)).IsInsideOrOn(ExpectedMoveLocalLocation) == false)
				{
					float ClosestLocalLocationXToZone = FMath::Clamp(ExpectedMoveLocalLocation.X, (-RestrictedZoneSize.X / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.X / 2.0f) - FLT_EPSILON);
					float ClosestLocalLocationYToZone = FMath::Clamp(ExpectedMoveLocalLocation.Y, (-RestrictedZoneSize.Y / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Y / 2.0f) - FLT_EPSILON);
					float ClosestLocalLocationZToZone = FMath::Clamp(ExpectedMoveLocalLocation.Z, (-RestrictedZoneSize.Z / 2.0f) + FLT_EPSILON, (RestrictedZoneSize.Z / 2.0f) - FLT_EPSILON);
					FVector ClosestWorldLocationToZone = RestrictedZoneTransform.TransformPosition(FVector(ClosestLocalLocationXToZone, ClosestLocalLocationYToZone, ClosestLocalLocationZToZone));
					ClosestWorldLocationToZone.Z = ViewCamera->GetActorLocation().Z;
					ViewCamera->SetActorLocation(ClosestWorldLocationToZone);
				}
				else
				{
					ViewCamera->AddActorWorldOffset(AppliedInertiaForceMagnitude);
				}

				if (InertiaForceMagnitude.Equals(FVector::ZeroVector, 0.001f) == true)
				{
					GetWorld()->GetTimerManager().ClearTimer(GenerateInertiaForceTimerHandle);
					InertiaForceMagnitude = FVector::ZeroVector;
				}
			}, 0.005f, true);
	}
}
