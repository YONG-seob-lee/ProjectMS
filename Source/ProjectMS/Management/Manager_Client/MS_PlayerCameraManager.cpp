#include "Management/Manager_Client/MS_PlayerCameraManager.h"

#include "MS_SceneManager.h"
#include "Camera/CameraModifier_CameraShake.h"

#include "Camera/ViewCamera/QuarterViewCamera/MS_QuarterViewCamera.h"
#include "Camera/ViewCamera/SideViewCamera/MS_SideViewCamera.h"
#include "Camera/ViewCamera/TopViewCamera/MS_TopViewCamera.h"

#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"
#include "Camera/CameraMode/FollowingPlayerCameraMode/MS_FollowingPlayerCameraMode.h"
#include "Camera/CameraMode/ImmobileCameraMode/MS_ImmobileCameraMode.h"

#include "Camera/CameraEffect/MS_CameraEffect.h"
#include "Camera/CameraEffect/CameraShake/MS_CameraShake.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "Table/Caches/MS_CommonCacheTable.h"

namespace ViewCamera
{
	const FName Quarter = TEXT("QuarterViewCamera");
	const FName Side = TEXT("SideViewCamera");
	const FName Top = TEXT("TopViewCamera");

	const FVector2D TownMax = FVector2D(14484.f, -5603.f);
	const FVector2D TownMin = FVector2D(10700.f, -10178.f);

	const FVector2D MarketMax = FVector2D(1500.f, 1000.f);
	const FVector2D MarketMin = FVector2D(-250.f, -1000.f);
}

AMS_PlayerCameraManager::AMS_PlayerCameraManager()
{
	CameraManager = this;
	CameraModeMap.Emplace(EMS_CameraModeType::FollowingInputCameraMode, CreateDefaultSubobject<UMS_FollowingInputCameraMode>(TEXT("FollowingInputCameraMode")));
	CameraModeMap.Emplace(EMS_CameraModeType::FollowingPlayerCameraMode, CreateDefaultSubobject<UMS_FollowingPlayerCameraMode>(TEXT("FollowingPlayerCameraMode")));
	CameraModeMap.Emplace(EMS_CameraModeType::ImmobileCameraMode, CreateDefaultSubobject<UMS_ImmobileCameraMode>(TEXT("ImmobileCameraMode")));

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
	FinalizeViewCamera();
	
	Super::Destroyed();
}

void AMS_PlayerCameraManager::InitializeViewCamera()
{
	FActorSpawnParameters ActorSpawnParameters = {};
	
	if(TObjectPtr<AMS_QuarterViewCamera> QuarterViewCamera = GetWorld()->SpawnActor<AMS_QuarterViewCamera>(AMS_QuarterViewCamera::StaticClass(), FTransform(FRotator(0.f, -90.f, 0.f), FVector::ZeroVector, FVector::OneVector), ActorSpawnParameters))
	{
		QuarterViewCamera->Deactivate();
		ActorSpawnParameters.Name = ViewCamera::Quarter;
		ViewCameraMap.Emplace(EMS_ViewCameraType::QuarterView, QuarterViewCamera);
	}

	if(TObjectPtr<AMS_SideViewCamera> SideViewCamera = GetWorld()->SpawnActor<AMS_SideViewCamera>(AMS_SideViewCamera::StaticClass(), FTransform(FRotator(45.f, -90.f, 0.f), FVector::ZeroVector, FVector::OneVector), ActorSpawnParameters))
	{
		SideViewCamera->Deactivate();
		ActorSpawnParameters.Name = ViewCamera::Side;
		ViewCameraMap.Emplace(EMS_ViewCameraType::SideView, SideViewCamera);
	}

	if(TObjectPtr<AMS_TopViewCamera> TopViewCamera = GetWorld()->SpawnActor<AMS_TopViewCamera>(AMS_TopViewCamera::StaticClass(), FTransform(FRotator(0.f, -90.f, 0.f), FVector::ZeroVector, FVector::OneVector), ActorSpawnParameters))
	{
		TopViewCamera->Deactivate();
		ActorSpawnParameters.Name = ViewCamera::Top;
		ViewCameraMap.Emplace(EMS_ViewCameraType::TopView, TopViewCamera);
	}
}

void AMS_PlayerCameraManager::FinalizeViewCamera()
{
	for(auto& ViewCamera : ViewCameraMap)
	{
		ViewCamera.Value->Deactivate();
		GetWorld()->DestroyActor(ViewCamera.Value);
	}

	ViewCameraMap.Empty();
}

void AMS_PlayerCameraManager::ReturnTarget(float aBlendTime)
{
	if(const TObjectPtr<AMS_ViewCamera>* QuarterCamera = ViewCameraMap.Find(EMS_ViewCameraType::QuarterView))
	{
		FViewTargetTransitionParams Params;
		Params.BlendTime = aBlendTime;

		if(aBlendTime > 0.f)
		{
			GetWorld()->GetTimerManager().SetTimer(CameraTransitionTimerHandle, [this]()
			{
				if(OnFinishedCameraTransition.IsBound())
				{
					OnFinishedCameraTransition.Execute();
					OnFinishedCameraTransition.Unbind();
				}
			}, aBlendTime, false);
		}
		SetViewTarget(*QuarterCamera, Params);
	}
}

void AMS_PlayerCameraManager::SwitchViewCamera(EMS_ViewCameraType aViewCameraType, FViewTargetTransitionParams aTransitionParam /* = FViewTargetTransitionParams() */)
{
	if (ViewCameraType == aViewCameraType)
	{
		return;
	}

	const TObjectPtr<class AMS_ViewCamera>* ViewCamera = ViewCameraMap.Find(aViewCameraType);
	if(ViewCamera == nullptr)
	{
		return;
	}
	
	const TObjectPtr<AMS_ViewCamera> TargetCamera = *ViewCamera;

	if (TargetCamera == nullptr)
	{
		MS_CHECK(TargetCamera);
		return;
	}

	if (CurrentCamera.IsValid() == true)
	{
		CurrentCamera->Deactivate();
	}

	ViewCameraType = aViewCameraType;
	CurrentCamera = TargetCamera;

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
	
	SetViewTarget(CurrentCamera.Get(), aTransitionParam);
}

void AMS_PlayerCameraManager::SwitchCameraMode(EMS_CameraModeType aCameraModeType)
{
	const TObjectPtr<class UMS_CameraMode>* pCameraMode = CameraModeMap.Find(aCameraModeType);
	if(pCameraMode == nullptr)
	{
		return;
	}
	UMS_CameraMode* TargetCameraMode = *pCameraMode;

	if (TargetCameraMode == nullptr || CurrentCameraMode == TargetCameraMode)
	{
		return;
	}

	if (CurrentCameraMode.IsValid() == true)
	{
		CurrentCameraMode->DeactivateMode();
	}

	CurrentCameraMode = TargetCameraMode;
	CurrentCameraMode->ActivateMode();
}

void AMS_PlayerCameraManager::AdjustPostProcessEffect(UMS_CameraPostProcessEffect* aCameraPostProcessEffect) const
{
	MS_ENSURE(CurrentCamera.Get());
	MS_ENSURE(aCameraPostProcessEffect);

	CurrentCamera->AdjustPostProcessEffect(aCameraPostProcessEffect);
}

TObjectPtr<AMS_ViewCamera> AMS_PlayerCameraManager::GetViewCamera(EMS_ViewCameraType aType)
{
	if(const TObjectPtr<AMS_ViewCamera>* TargetViewCamera = ViewCameraMap.Find(aType))
	{
		return *TargetViewCamera;
	}

	return nullptr;
}

void AMS_PlayerCameraManager::ZoomCamera(float aDistance)
{
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);

	const float CameraDistanceStrength = CommonTable->GetParameter02(CommonContents::CAMERA_DISTANCE_STRENGTH);
	EMS_LevelType LevelType = gSceneMng.GetCurrentLevelType();
	const float CameraDistanceMax = CommonTable->GetParameter02(LevelType == EMS_LevelType::MarketLevel ? CommonContents::MAX_CAMERA_DISTANCE_MARKET : CommonContents::MAX_CAMERA_DISTANCE_TOWN);
	const float CameraDistanceMin = CommonTable->GetParameter02(LevelType == EMS_LevelType::MarketLevel ? CommonContents::MIN_CAMERA_DISTANCE_MARKET : CommonContents::MIN_CAMERA_DISTANCE_TOWN);
	
	float TargetCameraDistance = CurrentCamera.Get()->CameraDistance + (-aDistance * CameraDistanceStrength);
	TargetCameraDistance = FMath::Clamp(TargetCameraDistance, CameraDistanceMin, CameraDistanceMax);

	const float NewInertiaForce = FMath::Clamp((TargetCameraDistance - CurrentCamera.Get()->CameraDistance) * 0.9f, -100.0f, 100.0f);

	if (GetWorld()->GetTimerManager().IsTimerActive(CameraInertiaTimerHandle))
	{
		CameraInertiaForce = NewInertiaForce;
		return;
	}

	CameraInertiaForce = NewInertiaForce;

	GetWorld()->GetTimerManager().SetTimer(CameraInertiaTimerHandle, [this, CameraDistanceMax, CameraDistanceMin]()
		{
			CameraInertiaForce *= 0.9f;

			if (FMath::Abs(CameraInertiaForce) < 0.01f)
			{
				CameraInertiaForce = 0.0f;
				GetWorld()->GetTimerManager().ClearTimer(CameraInertiaTimerHandle);
				return;
			}

			float NewCameraDistance = CurrentCamera.Get()->CameraDistance + CameraInertiaForce;

			const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
			MS_ENSURE(CommonTable);
		
			NewCameraDistance = FMath::Clamp(NewCameraDistance, CameraDistanceMin, CameraDistanceMax);

			CurrentCamera.Get()->AdjustCameraDistance(NewCameraDistance);

		}, 0.01f, true);
}

void AMS_PlayerCameraManager::OrbitCamera(float aFloat)
{
}

void AMS_PlayerCameraManager::ShakeCamera(float aIntensity, float aDuration)
{
	FAddCameraShakeParams AddCameraShakeParams = {};
	AddCameraShakeParams.Scale = aIntensity;
	AddCameraShakeParams.DurationOverride = aDuration;

	StartCameraShake(UMS_CameraShake::StaticClass(), AddCameraShakeParams);
}

void AMS_PlayerCameraManager::LocateCamera(const FVector& aLocation, EMS_ViewCameraType aViewCameraType /*  = EMS_ViewCameraType::QuarterView */)
{
	if(const TObjectPtr<AMS_ViewCamera>* TargetViewCamera = ViewCameraMap.Find(aViewCameraType))
	{
		(*TargetViewCamera)->SetActorLocation(aLocation);
	}
}

void AMS_PlayerCameraManager::LocateCamera(const FVector& aLocation) const
{
	if(CurrentCamera.IsValid())
	{
		CurrentCamera->SetActorLocation(aLocation);
	}
}

void AMS_PlayerCameraManager::RotateCamera(const FRotator& aRotation) const
{
	if(CurrentCamera.IsValid())
	{
		CurrentCamera->SetActorRotation(aRotation);
	}
}

void AMS_PlayerCameraManager::SetQuarterViewTilt(EMS_TiltType aTiltType)
{
	const TObjectPtr<class AMS_ViewCamera>* ViewCamera = ViewCameraMap.Find(EMS_ViewCameraType::QuarterView);
	if(!ViewCamera)
	{
		return;
	}
	const TObjectPtr<AMS_QuarterViewCamera> QuarterViewCamera = Cast<AMS_QuarterViewCamera>(*ViewCamera);
	if(!QuarterViewCamera)
	{
		return;
	}
	
	QuarterViewCamera->SetTilt(aTiltType);
}

void AMS_PlayerCameraManager::DollyIn(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldOffset(FVector(1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::DollyOut(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldOffset(FVector(-1.0f, 0.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::TruckLeft(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldOffset(FVector(0.0f, -1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::TruckRight(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldOffset(FVector(0.0f, 1.0f, 0.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::DollyAndTruck(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend)
{
	if (bRestrictCameraFlag == true)
	{
		return;
	}

	if(gSceneMng.GetCurrentLevelType() == EMS_LevelType::LobbyLevel)
	{
		MoveDensity = 3.f;
		CheckRegistCameraPosition(EMS_LevelType::Stage01, CurrentCamera->GetActorLocation(), aPointerGlidePositionDeltaTrend);
	}
	else if(gSceneMng.GetCurrentLevelType() == EMS_LevelType::MarketLevel)
	{
		MoveDensity = 0.8f;
		CheckRegistCameraPosition(EMS_LevelType::MarketLevel, CurrentCamera->GetActorLocation(), aPointerGlidePositionDeltaTrend);
	}
		
	CurrentCamera->AddActorWorldOffset(FVector(-aPointerGlidePositionDeltaTrend.X, -aPointerGlidePositionDeltaTrend.Y, 0.0f) * MoveSensitivity);
	GenerateInertiaForce(FVector(-aPointerGlidePositionDeltaTrend.X, -aPointerGlidePositionDeltaTrend.Y, 0.0f) * MoveDensity);
}

void AMS_PlayerCameraManager::PedestalUp(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldOffset(FVector(0.0f, 0.0f, 1.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::PedestalDown(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldOffset(FVector(0.0f, 0.0f, -1.0f) * aValue.Get<float>() * MoveSensitivity);
	}
}

void AMS_PlayerCameraManager::RollCounterclockwise(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldRotation(FRotator(0.0f, 0.0f, -1.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::RollClockwise(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldRotation(FRotator(0.0f, 0.0f, 1.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::TiltUp(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldRotation(FRotator(1.0f, 0.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::TiltDown(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldRotation(FRotator(-1.0f, 0.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::PanLeft(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldRotation(FRotator(0.0f, -1.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}
void AMS_PlayerCameraManager::PanRight(const FInputActionValue& aValue)
{
	if (aValue.Get<float>() != 0.0f)
	{
		CurrentCamera->AddActorWorldRotation(FRotator(0.0f, 1.0f, 0.0f) * aValue.Get<float>() * TurnSensitivity);
	}
}

void AMS_PlayerCameraManager::DEBUG_INPUT_OrbitCamera(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend)
{
	TargetCameraRotation = CurrentCamera.Get()->GetActorRotation();
	TargetCameraRotation.Yaw += aPointerGlidePositionDelta.X * 0.9f;

	if (!GetWorld()->GetTimerManager().IsTimerActive(CameraRotationTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(CameraRotationTimerHandle, [this]()
			{
				FRotator CurrentRotation = CurrentCamera.Get()->GetActorRotation();

				static float VelocityYaw = 0.0f;

				FRotator NewRotation = GenerateInertiaForceForRotation(CurrentRotation, TargetCameraRotation, VelocityYaw, 0.2f);
				NewRotation.Yaw = FMath::Clamp(NewRotation.Yaw, -45.0f, 45.0f);

				CurrentCamera.Get()->SetActorRotation(NewRotation);

				if (FMath::Abs(VelocityYaw) < 0.01f && FMath::IsNearlyEqual(NewRotation.Yaw, TargetCameraRotation.Yaw, 0.01f))
				{
					GetWorld()->GetTimerManager().ClearTimer(CameraRotationTimerHandle);
				}
			}, 0.005f, true);
	}
}

void AMS_PlayerCameraManager::GenerateInertiaForce(const FVector& aMagnitude)
{
	InertiaForceMagnitude += aMagnitude;

	if (!GetWorld()->GetTimerManager().IsTimerActive(GenerateInertiaForceTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(GenerateInertiaForceTimerHandle, [&]()
			{
				const FVector AppliedInertiaForceMagnitude = InertiaForceMagnitude * 0.025f;
				InertiaForceMagnitude -= AppliedInertiaForceMagnitude;

				const FVector NewCameraLocation = CurrentCamera->GetActorLocation() + AppliedInertiaForceMagnitude;
				CurrentCamera->SetActorLocation(NewCameraLocation);

				if (InertiaForceMagnitude.Equals(FVector::ZeroVector, 0.001f))
				{
					GetWorld()->GetTimerManager().ClearTimer(GenerateInertiaForceTimerHandle);
					InertiaForceMagnitude = FVector::ZeroVector;
				}
			}, 0.005f, true);
	}
}

FRotator AMS_PlayerCameraManager::GenerateInertiaForceForRotation(const FRotator& aCurrentRotation, const FRotator& aTargetRotation, float& aVelocity, float aDampingFactor)
{
	const FRotator Delta = aTargetRotation - aCurrentRotation;
	aVelocity += Delta.Yaw * aDampingFactor;
	aVelocity *= aDampingFactor;

	return aCurrentRotation + FRotator(0.0f, aVelocity, 0.0f);
}

void AMS_PlayerCameraManager::CheckRegistCameraPosition(EMS_LevelType LevelType, const FVector& CameraPosition,
	FVector2D& PointerGlidePositionDeltaTrend)
{
	const FVector2D NextCameraLocation = FVector2D(CameraPosition.X, CameraPosition.Y) + (-PointerGlidePositionDeltaTrend);
	const FVector2D Max = LevelType == EMS_LevelType::MarketLevel ? ViewCamera::MarketMax : ViewCamera::TownMax;
	const FVector2D Min = LevelType == EMS_LevelType::MarketLevel ? ViewCamera::MarketMin : ViewCamera::TownMin;
	
	if(NextCameraLocation.X > Max.X)
	{
		PointerGlidePositionDeltaTrend.X = NextCameraLocation.X - Max.X;
	}
	if(NextCameraLocation.X < Min.X)
	{
		PointerGlidePositionDeltaTrend.X = NextCameraLocation.X - Min.X;
	}
	if(NextCameraLocation.Y > Max.Y)
	{
		PointerGlidePositionDeltaTrend.Y = NextCameraLocation.Y - Max.Y;
	}
	if(NextCameraLocation.Y < Min.Y)
	{
		PointerGlidePositionDeltaTrend.Y = NextCameraLocation.Y - Min.Y;
	}
}

AMS_PlayerCameraManager* AMS_PlayerCameraManager::GetInstance()
{
	return CameraManager;
}
