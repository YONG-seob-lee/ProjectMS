// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StateBase.h"

void UMS_StateBase::Initialize(uint8 aIndex, const FName& aName)
{
	StateIndex = aIndex;
	StateName = aName;
}

void UMS_StateBase::Finalize()
{
}

void UMS_StateBase::OnBeginState()
{
	Begin();
}

void UMS_StateBase::OnTickState()
{
}

void UMS_StateBase::OnExitState()
{
	Exit();
}
