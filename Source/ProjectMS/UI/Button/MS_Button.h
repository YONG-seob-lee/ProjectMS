// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "MS_Button.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_Button : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	UMS_Button();
	virtual ~UMS_Button() override;
	virtual void NativeConstruct() override;
	
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual const FText GetPaletteCategory() override;

	FCommonButtonEvent& GetOnClickedDelegate() { SetDelegates(); return MS_OnClickedDelegate; }
	FORCEINLINE void UnbindClickedDelegate() { MS_OnClickedDelegate.Clear(); }
	void SetOnPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_OnPressedDelegate = Delegate; }
	FORCEINLINE void UnbindPressedDelegate() { MS_OnPressedDelegate.Clear(); }
	void SetOnReleasedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_OnReleasedDelegate = Delegate; }
	FORCEINLINE void UnbindReleasedDelegate() { MS_OnReleasedDelegate.Clear(); }
	void SetOnHoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_OnHoveredDelegate = Delegate; }
	FORCEINLINE void UnbindHoveredDelegate() { MS_OnHoveredDelegate.Clear(); }
	void SetOnUnhoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_OnUnhoveredDelegate = Delegate; };
	FORCEINLINE void UnbindUnhoveredDelegate() { MS_OnUnhoveredDelegate.Clear(); }
	void SetWillCloseWidgetDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_WillCloseWidgetDelegate = Delegate; };
	FORCEINLINE void UnbindWillCloseWidgetDelegate() { MS_WillCloseWidgetDelegate.Clear(); }
	void SetWillCreateSceneDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_WillCreateSceneDelegate = Delegate; };
	FORCEINLINE void UnbindWillCreateSceneDelegate() { MS_WillCreateSceneDelegate.Clear(); }
	void SetPlayAnimDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_PlayAnimDelegate = Delegate; };
	FORCEINLINE void UnbindPlayAnimDelegate() { MS_PlayAnimDelegate.Clear(); }
	void SetOnClickedInDelayTimeDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_OnClickedInDelayTimeDelegate = Delegate; };
	FORCEINLINE void UnbindClickedInDelayTimeDelegate() { MS_OnClickedInDelayTimeDelegate.Clear(); }
	void SetOnLongPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); MS_OnLongPressedDelegate = Delegate; };
	FORCEINLINE void UnbindLongPressedDelegate() { MS_OnLongPressedDelegate.Clear(); }

	FORCEINLINE void SetCustomVector(const FVector& Vector) { CustomVector = Vector;}
	FORCEINLINE FVector GetCustomVector() const { return CustomVector; }

	void OnHoverJoyStick();
	void UnHoverJoyStick();
private:
	void SetDelegates();
	
	UFUNCTION() void OnClick();
	UFUNCTION() void OnPress();
	UFUNCTION() void OnRelease();
	UFUNCTION() void OnHover();
	UFUNCTION() void OnUnHover();

	FORCEINLINE bool IsUseClockedDelay() const { return bUseClickedDelay && 0.f < ClickedDelayTime; }
	FORCEINLINE bool IsUseLongPressedEvent() const { return bUseLongPressedEvent && 0.f < LongPressedTime && GetWorld() != nullptr; }
	
protected:	
	UPROPERTY(Category = UMS_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseClickedDelay = false;
	UPROPERTY(Category = UMS_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseClickedDelay"))
	float ClickedDelayTime = 0.f;
	UPROPERTY(Category = UMS_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseReleasedDelay = false;
	UPROPERTY(Category = UMS_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseReleasedDelay"))
	float ReleasedDelayTime = 0.f;
	UPROPERTY(Category = UMS_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseLongPressedEvent = false;
	UPROPERTY(Category = UMS_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseLongPressedEvent"))
	float LongPressedTime = 0.f;
	
	FCommonButtonEvent MS_OnClickedDelegate;
	FCommonButtonEvent MS_OnPressedDelegate;
	FCommonButtonEvent MS_OnReleasedDelegate;
	FCommonButtonEvent MS_OnHoveredDelegate;
	FCommonButtonEvent MS_OnUnhoveredDelegate;

	FCommonButtonEvent MS_OnClickedInDelayTimeDelegate;
	FCommonButtonEvent MS_OnLongPressedDelegate;

	FCommonButtonEvent MS_PlayAnimDelegate;
	FCommonButtonEvent MS_WillCloseWidgetDelegate;
	FCommonButtonEvent MS_WillCreateSceneDelegate;

	FTimerHandle PressTimerHandle;
	
	float LastClickedTime = 0.f;
	float LastReleasedTime = 0.f;

	FVector CustomVector = FVector::ZeroVector;
};
