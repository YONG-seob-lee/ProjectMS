// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Management/MS_ManagerBase.h"
#include "Widget/MS_RootWidget.h"
#include "Widget/System/Modal/MS_ModalWidget.h"
#include "MS_WidgetManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMS_CreateWidget, const FName&);
DECLARE_MULTICAST_DELEGATE_OneParam(FMS_DestroyWidget, const FName&);

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_WidgetManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_WidgetManager();
	
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void PreFinalize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;

	virtual void Tick(float aDeltaTime) override;
	
	TObjectPtr<class UMS_Widget> GetWidget(const FName& aTypeName);
	TObjectPtr<class UMS_Widget> Create_Widget(const FName& aTypeName, bool bAttachToRoot = true);
	TObjectPtr<class UMS_Widget> Create_Widget_NotManaging(const FSoftObjectPath& aSoftObjectPath) const;

	void PreDestroyWidget(const TObjectPtr<class UMS_Widget>& aWidget) const;
	bool DestroyWidget(const FName& aTypeName);
	bool DestroyWidget(TObjectPtr<UMS_Widget> aWidget);
	void PostDestroyWidget(const FName& aTypeName);

	void HideAllWidget(bool bHide) const;
	
	void ActivatePreventionCover(bool bActivate) const;
	void ShowMessageOnScreen(const FString& aMessage, bool bNewerOnTop = true, float aElapsedTime = 3.f, FColor aDisplayColor = FColor::Green);
	void ShowToastMessage(const FString& aMessage) const;
	
	void ShowRotateWidget() const;
	void HideRotateWidget() const;

	void ShowModalWidget(const FMS_ModalParameter& aModalParameter = FMS_ModalParameter()) const;
	void CloseModalWidget(const TFunction<void()>& _OnCloseModalWidgetCallback = nullptr) const;

	void SetCustomPositionWidget(UMS_Widget* aWidget, const FVector2D& aPosition);

	void RequestDialog(const TArray<FMS_DialogParameter>& aDialogParameters) const;

	FMS_CreateWidget OnCreateWidget;
	FMS_DestroyWidget OnDestroyWidget;

	void CreateRoot();
	void AttachToRoot(const TObjectPtr<UMS_Widget>& aWidget) const;
	void RefreshContentWidget();
	
	FORCEINLINE TObjectPtr<UMS_RootWidget> GetRootWidget() { return RootWidget; }
	
private:
	TObjectPtr<class UMS_Widget> CreateWidget_Internal(const FName& aTypeName, bool bManaged, bool bAttachToRoot = true);
	TObjectPtr<class UMS_Widget> CreateWidget_Internal_Managing(const FString& aPath);
	TObjectPtr<class UMS_Widget> CreateWidget_Internal_NotManaging(const FString& aPath) const;
	
	void LoadComplete(const FString& aTableName, TObjectPtr<UObject> aWidgetData);
	
	void RequestCustomPosition(const TObjectPtr<UMS_Widget>& aWidget, const FVector2D& aPosition);
	
	UPROPERTY()
	TMap<FName, TWeakObjectPtr<class UMS_Widget>> ManagedWidgets;

	UPROPERTY()
	TObjectPtr<UMS_RootWidget> RootWidget = nullptr;

	TWeakObjectPtr<UMS_Widget> CustomPositionWidget = nullptr;
	FVector2D CustomPosition = FVector2D::ZeroVector;
	
public:
	inline static TObjectPtr<UMS_WidgetManager> WidgetManager = nullptr;
	static UMS_WidgetManager* GetInstance();
	
#define gWidgetMng (*UMS_WidgetManager::GetInstance())
};
