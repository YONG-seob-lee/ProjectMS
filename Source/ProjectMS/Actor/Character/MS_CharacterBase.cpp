#include "MS_CharacterBase.h"

#include "Components/SphereComponent.h"
#include "Unit/MS_UnitBase.h"
#include "Unit/UnitState/MS_UnitStateBase.h"


AMS_CharacterBase::AMS_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Activate();

		// if(const TObjectPtr<UCY_AnimInstance> AnimInstance = GetAnimInstance())
		// {
		// 	AnimInstance->Initialize();
		// }

		RootSkeletalMeshComponent->bUseAsOccluder = false;
	}

	TestSphere = CreateDefaultSubobject<USphereComponent>("VisibleTestComponent");
	if(TestSphere)
	{
		TestSphere->SetSphereRadius(300.f);
		TestSphere->SetGenerateOverlapEvents(false);
		TestSphere->SetEnableGravity(false);
		TestSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TestSphere->SetCollisionProfileName(TEXT("NoCollision"));
		TestSphere->SetupAttachment(RootComponent);
		RootSkeletalMeshComponent->SetupAttachment(TestSphere);
	}
}

void AMS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_CharacterBase::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_CharacterBase::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(aPlayerInputComponent);

	// TODO:
	const TObjectPtr<UMS_UnitBase> Unit = Cast<UMS_UnitBase>(GetOuter());
	MS_CHECK(Unit);

	const TObjectPtr<UMS_UnitStateBase> UnitStateBase = Cast<UMS_UnitStateBase>(Unit->GetCurrentUnitState());
	MS_CHECK(UnitStateBase);
}

void AMS_CharacterBase::Create(const FString& aLabelName)
{
	SetActorLabel(aLabelName);

	Initialize();
}

void AMS_CharacterBase::Destroy()
{
	Finalize();
}

void AMS_CharacterBase::Initialize()
{
}

void AMS_CharacterBase::Finalize()
{
	if(TestSphere)
	{
		TestSphere->Deactivate();
	}

	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Deactivate();

		// if(const TObjectPtr<UMS_AnimInstance> _AnimInstance = GetAnimInstance())
		// {
		// 	_AnimInstance->Finalize();
		// }
	}
}

void AMS_CharacterBase::SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine)
{
	LodValues.CullDistanceScale = aCullDistanceScale;
	LodValues.OutLineCullDistanceScale = aOutLineCullDistanceScale;
	LodValues.bVisibleOutLine = bVisibleOutLine;
}

