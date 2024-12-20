#include "MS_ModeStateBase.h"


UMS_ModeStateBase::UMS_ModeStateBase()
{
	
}

void UMS_ModeStateBase::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);
}

void UMS_ModeStateBase::Finalize()
{
	Super::Finalize();
}

void UMS_ModeStateBase::Tick(float aDeltaTime)
{
}

void UMS_ModeStateBase::Begin()
{
}

void UMS_ModeStateBase::Exit()
{
}

void UMS_ModeStateBase::OnInputPointerDown()
{
}

void UMS_ModeStateBase::OnInputPointerUp()
{
}

void UMS_ModeStateBase::OnInputPointerMove()
{
}

void UMS_ModeStateBase::OnInputPointerHold()
{
}

void UMS_ModeStateBase::OnInputPointerClick()
{
}

void UMS_ModeStateBase::OnInputPointerGlide()
{
}
