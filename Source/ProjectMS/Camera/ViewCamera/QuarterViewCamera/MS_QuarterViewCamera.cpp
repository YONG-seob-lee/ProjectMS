#include "Camera/ViewCamera/QuarterViewCamera/MS_QuarterViewCamera.h"

#include "Camera/CameraComponent.h"

AMS_QuarterViewCamera::AMS_QuarterViewCamera()
{
	SceneComponent->SetAbsolute(false, true, true);
	SetActorEnableCollision(true);
	CameraDistance = 300.0f;
	CameraComponent->SetRelativeLocationAndRotation(FVector(-CameraDistance, 0.0f, CameraDistance), FRotator(0.f, 0.0f, 0.0f));
	Tilts.Emplace(EMS_TiltType::VeryVeryLow, -30.f);
	Tilts.Emplace(EMS_TiltType::VeryLow, -40.f);
	Tilts.Emplace(EMS_TiltType::Low, -50.f);
	Tilts.Emplace(EMS_TiltType::Default, -60.f);
	Tilts.Emplace(EMS_TiltType::High, -70.f);
	Tilts.Emplace(EMS_TiltType::VeryHigh, -80.f);
	Tilts.Emplace(EMS_TiltType::VeryVeryHigh, -90.f);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if(StaticMeshComponent)
	{
		SetRootComponent(StaticMeshComponent);
		CameraComponent->SetupAttachment(StaticMeshComponent);

		if(UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Environment/CameraBlock/CameraDummySphere.CameraDummySphere"))))
		{
			StaticMeshComponent->SetStaticMesh(Mesh);
			StaticMeshComponent->SetCollisionProfileName(TEXT("CameraBlock"));
		}
	}
	SetHidden(true);
}

void AMS_QuarterViewCamera::BeginPlay()
{
	Super::BeginPlay();
	
	AdjustCameraDistance(CameraDistance);
}

void AMS_QuarterViewCamera::AdjustCameraDistance(float aDistance)
{
    Super::AdjustCameraDistance(aDistance);

	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	if(const float* TiltValue = Tilts.Find(GameUserSettings->GetQuarterViewCameraTiltType()))
	{
		CameraComponent->SetRelativeLocationAndRotation(FVector(-CameraDistance, 0.0f, CameraDistance), FRotator(*TiltValue, 0.0f, 0.0f));
	}
}

void AMS_QuarterViewCamera::SetTilt(EMS_TiltType aTiltType)
{
	const float* TiltValue = Tilts.Find(aTiltType);
	if(!TiltValue)
	{
		return;
	}

	CameraComponent->SetRelativeRotation(FRotator(*TiltValue, 0.f, 0.f));
}

void AMS_QuarterViewCamera::Activate()
{
	Super::Activate();
}

void AMS_QuarterViewCamera::Deactivate()
{
	Super::Deactivate();
}