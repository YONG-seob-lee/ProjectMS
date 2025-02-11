#include "Actor/Prop/Furniture/Storage/MS_Storage.h"


AMS_Storage::AMS_Storage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
}

void AMS_Storage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Storage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Storage::OnSelectNormal()
{
	CreateStorageWidget();
}

void AMS_Storage::OnUnselectNormal()
{
	CreateStorageWidget();
}

void AMS_Storage::CreateStorageWidget()
{
}

void AMS_Storage::DestroyStorageWidget()
{
}
