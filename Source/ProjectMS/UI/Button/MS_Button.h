// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Widget/MS_Widget.h"
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
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	FCommonButtonEvent& GetOnClickedDelegate() { SetDelegates(); return MS_OnClickedDelegate; }
	FORCEINLINE void UnbindClickedDelegate() { MS_OnClickedDelegate.Clear(); }
	FCommonButtonEvent& GetOnPressedDelegate() { SetDelegates(); return MS_OnPressedDelegate; }
	FORCEINLINE void UnbindPressedDelegate() { MS_OnPressedDelegate.Clear(); }
	FCommonButtonEvent& GetOnReleasedDelegate() { SetDelegates(); return MS_OnReleasedDelegate; }
	FORCEINLINE void UnbindReleasedDelegate() { MS_OnReleasedDelegate.Clear(); }
	FCommonButtonEvent& GetOnHoveredDelegate() { SetDelegates(); return MS_OnHoveredDelegate; }
	FORCEINLINE void UnbindHoveredDelegate() { MS_OnHoveredDelegate.Clear(); }
	FCommonButtonEvent& GetOnUnhoveredDelegate() { SetDelegates(); return MS_OnUnhoveredDelegate; };
	FORCEINLINE void UnbindUnhoveredDelegate() { MS_OnUnhoveredDelegate.Clear(); }
	FCommonButtonEvent& GetWillCloseWidgetDelegate() { SetDelegates(); return MS_WillCloseWidgetDelegate; };
	FORCEINLINE void UnbindWillCloseWidgetDelegate() { MS_WillCloseWidgetDelegate.Clear(); }
	FCommonButtonEvent& GetWillCreateSceneDelegate() { SetDelegates(); return MS_WillCreateSceneDelegate; };
	FORCEINLINE void UnbindWillCreateSceneDelegate() { MS_WillCreateSceneDelegate.Clear(); }
	FCommonButtonEvent& GetPlayAnimDelegate() { SetDelegates(); return MS_PlayAnimDelegate; };
	FORCEINLINE void UnbindPlayAnimDelegate() { MS_PlayAnimDelegate.Clear(); }
	FCommonButtonEvent& GetOnClickedInDelayTimeDelegate() { SetDelegates(); return MS_OnClickedInDelayTimeDelegate; };
	FORCEINLINE void UnbindClickedInDelayTimeDelegate() { MS_OnClickedInDelayTimeDelegate.Clear(); }
	FCommonButtonEvent& GetOnLongPressedDelegate() { SetDelegates(); return MS_OnLongPressedDelegate; };
	FORCEINLINE void UnbindLongPressedDelegate() { MS_OnLongPressedDelegate.Clear(); }

	FORCEINLINE void SetCustomVector(const FVector& Vector) { CustomVector = Vector;}
	FORCEINLINE FVector GetCustomVector() const { return CustomVector; }

	void OnHoverJoyStick();
	void UnHoverJoyStick();
	
	virtual void PlayTutorial(const FString& Desc, const FString& SubDesc);
	
private:
	void SetDelegates();
	
	UFUNCTION() void OnClick();
	UFUNCTION() void OnPress();
	UFUNCTION() void OnRelease();
	UFUNCTION() void OnHover();
	UFUNCTION() void OnUnHover();

	FORCEINLINE bool IsUseClockedDelay() const { return bUseClickedDelay && 0.f < ClickedDelayTime; }
	FORCEINLINE bool IsUseLongPressedEvent() const { return bUseLongPressedEvent && 0.f < LongPressedTime && GetWorld() != nullptr; }
	
	
	TObjectPtr<class UNamedSlot> GetNamedSlot() const;
	void RePositionNamedSlot(const TObjectPtr<UPanelSlot>& NamedSlot) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "True"))
	EMS_TutorialDirection TutorialDirection = EMS_TutorialDirection::UpToRight;
	
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
