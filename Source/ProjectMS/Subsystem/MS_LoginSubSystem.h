// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "MS_LoginSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LoginSubSystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	TSharedPtr<class IMS_AuthenticationInterface> AuthManager;

	template<typename T>
	void SetAuthManager()
	{
		AuthManager = MakeShared<T>();
	}

	TSharedPtr<IMS_AuthenticationInterface> GetAuthManager() const { return AuthManager;}
};
