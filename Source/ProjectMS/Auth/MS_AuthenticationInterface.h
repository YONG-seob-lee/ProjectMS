// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class PROJECTMS_API IMS_AuthenticationInterface
{
public:
	virtual ~IMS_AuthenticationInterface() = default;
	virtual void Login() = 0;
	virtual void Logout() = 0;
	virtual bool IsLoginedIn() const = 0;
};

class FMS_GoogleLoginManager : public IMS_AuthenticationInterface
{
public:
	virtual void Login() override;
	virtual void Logout() override;
	virtual bool IsLoginedIn() const override;

	FORCEINLINE void SetOnGoogleLoginFunc(const TFunction<void()>& _Func) { OnGoogleLoginCallback = _Func; }
	
private:
	void OnGoogleLoginComplete(int32 _Index, bool bSuccessful, const FUniqueNetId& _UserId, const FString& _ErrorString);
	void OnGoogleLogoutComplete(int32 _MaxLocalPlayers, bool bOnLogoutComplete);

	TFunction<void()> OnGoogleLoginCallback = nullptr;
};
