// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Management/MS_ManagerBase.h"
#include "Management/SceneManager/MS_SceneManager.h"
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
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void PreFinalize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;

	virtual void Tick(float aDeltaTime) override;
	
	TObjectPtr<class UMS_Widget> GetWidget(const FName& aTypeName);
	TObjectPtr<class UMS_Widget> Create_Widget(const FName& aTypeName);
	TObjectPtr<class UMS_Widget> Create_Widget_NotManaging(const FSoftObjectPath& aSoftObjectPath);

	void PreDestroyWidget(TObjectPtr<class UMS_Widget> aWidget);
	bool DestroyWidget(const FName& aTypeName);
	void PostDestroyWidget(const FName& aTypeName);
	
	TObjectPtr<UMS_Widget> GetCurrentWidget();
	void SetCurrentWidget(const TObjectPtr<UMS_Widget>& aCurrentWidget);

	FMS_CreateWidget OnCreateWidget;
	FMS_DestroyWidget OnDestroyWidget;

private:
	TObjectPtr<class UMS_Widget> CreateWidget_Internal(const FName& aTypeName, bool bManaged);
	TObjectPtr<class UMS_Widget> CreateWidget_Internal_Managing(const FString& aPath);
	TObjectPtr<class UMS_Widget> CreateWidget_Internal_NotManaging(const FString& aPath) const;
	
	void LoadComplete(const FString& aTableName, TObjectPtr<UObject> aWidgetData);
	
	UPROPERTY()
	TMap<FName, TWeakObjectPtr<class UMS_Widget>> ManagedWidgets;
};
