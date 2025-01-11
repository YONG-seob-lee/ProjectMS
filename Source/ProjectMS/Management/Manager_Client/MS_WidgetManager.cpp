// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_WidgetManager.h"

#include "CoreClass/Controller/MS_PlayerController.h"
#include "Data/Table/Caches/MS_ResourceWidgetCacheTable.h"
#include "Data/Table/RowBase/MS_ResourceWidget.h"
#include "Engine/AssetManager.h"
#include "Manager_Both/MS_TableManager.h"
#include "UI/Widget/MS_Widget.h"
#include "Utility/MS_Define.h"
#include "Widget/MS_RootWidget.h"

UMS_WidgetManager::UMS_WidgetManager()
{
	WidgetManager = this;
}

void UMS_WidgetManager::BuiltInInitialize()
{
	Super::BuiltInInitialize();
}

void UMS_WidgetManager::Initialize()
{
	Super::Initialize();
}

void UMS_WidgetManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_WidgetManager::PreFinalize()
{
	Super::PreFinalize();
}

void UMS_WidgetManager::Finalize()
{
	Super::Finalize();
}

void UMS_WidgetManager::BuiltInFinalize()
{
	Super::BuiltInFinalize();
}

void UMS_WidgetManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

TObjectPtr<UMS_Widget> UMS_WidgetManager::GetWidget(const FName& aTypeName)
{
	const TWeakObjectPtr<UMS_Widget>* pWidget = ManagedWidgets.Find(aTypeName);
	if(pWidget && pWidget->IsValid())
	{
		return pWidget->Get();
	}

	return nullptr;
}

TObjectPtr<UMS_Widget> UMS_WidgetManager::Create_Widget(const FName& aTypeName, bool bAttachToRoot /* = true */)
{
	GEngine->ForceGarbageCollection(true);

	if(const TWeakObjectPtr<UMS_Widget>* pWidget = ManagedWidgets.Find(aTypeName))
	{
		const TWeakObjectPtr<UMS_Widget>& PreviousWidget = *pWidget;
		if(PreviousWidget.IsValid())
		{
			return PreviousWidget.Get();
		}
		ManagedWidgets.Remove(aTypeName);
	}

	const TObjectPtr<UMS_Widget> Widget = Cast<UMS_Widget>(CreateWidget_Internal(aTypeName, true, bAttachToRoot));
	MS_CHECK(Widget != nullptr);

	ManagedWidgets.Emplace(aTypeName, Widget);

	if(bAttachToRoot)
	{
		AttachToRoot(Widget);
	}
	
	if(OnCreateWidget.IsBound())
	{
		OnCreateWidget.Broadcast(aTypeName);
	}
	
	return Widget;
}

TObjectPtr<UMS_Widget> UMS_WidgetManager::Create_Widget_NotManaging(const FSoftObjectPath& aSoftObjectPath)
{
	const TObjectPtr<UMS_Widget> Widget = CreateWidget_Internal_NotManaging(aSoftObjectPath.ToString());
	if(Widget == nullptr)
	{
		MS_CHECK(false);
		return nullptr;
	}
	
	return Widget;
}

void UMS_WidgetManager::PreDestroyWidget(TObjectPtr<UMS_Widget> aWidget)
{
	if(IsValid(aWidget) == false)
	{
		return;
	}

	if(OnDestroyWidget.IsBound())
	{
		OnDestroyWidget.Broadcast(aWidget->GetResourceWidgetInfo().GetWidgetName());
	}
}

bool UMS_WidgetManager::DestroyWidget(const FName& aTypeName)
{
	TObjectPtr<UMS_Widget> Widget = GetWidget(aTypeName);
	if(Widget == nullptr)
	{
		return false;
	}

	PreDestroyWidget(Widget);
	Widget->FinishWidget();

	ManagedWidgets.Remove(aTypeName);
	Widget = nullptr;
	PostDestroyWidget(aTypeName);	
	return true;
}

void UMS_WidgetManager::PostDestroyWidget(const FName& aTypeName)
{
}

void UMS_WidgetManager::ShowMessageOnScreen(const FString& aMessage, bool bNewerOnTop, float aElapsedTime, FColor aDisplayColor)
{
	GEngine->AddOnScreenDebugMessage(-1, aElapsedTime, aDisplayColor, aMessage);
}

void UMS_WidgetManager::ShowToastMessage(const FString& aMessage) const
{
	if(RootWidget)
	{
		RootWidget->ShowToastMessage(aMessage);
	}
}

void UMS_WidgetManager::ShowRotateWidget() const
{
	if(RootWidget)
	{
		RootWidget->ShowRotateWidget();
	}
}

void UMS_WidgetManager::HideRotateWidget() const
{
}

void UMS_WidgetManager::ShowModalWidget(const TObjectPtr<UMS_Widget>& aNewWidget, bool bShow /* = true */, const FName AnimationName /* = FName() */) const
{
	RootWidget->ShowModalWidget(aNewWidget, bShow, AnimationName);
}

void UMS_WidgetManager::ShowGeneralWidget(bool bShow) const
{
	RootWidget->ShowGeneralWidget(bShow);
}

void UMS_WidgetManager::CreateRoot()
{
	RootWidget = Cast<UMS_RootWidget>(Create_Widget(UMS_RootWidget::GetWidgetName(), false));
}

void UMS_WidgetManager::AttachToRoot(const TObjectPtr<UMS_Widget>& aWidget)
{
	RootWidget->AttachContentWidget(aWidget);
}

void UMS_WidgetManager::RefreshContentWidget() 
{
	MS_CHECK(RootWidget);
	RootWidget->RefreshContentCanvas();

	ManagedWidgets.Empty();
}

TObjectPtr<UMS_Widget> UMS_WidgetManager::CreateWidget_Internal(const FName& aTypeName, bool bManaged, bool bAttachToRoot/* = true */)
{	
	const TObjectPtr<UMS_ResourceWidgetCacheTable> ResourceWidgetCache = Cast<UMS_ResourceWidgetCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ResourceWidget));
	if(ResourceWidgetCache == nullptr)
	{
		return nullptr;
	}

	const FMS_ResourceWidget* ResourceWidgetData = ResourceWidgetCache->GetResourceWidgetData(aTypeName);
	if(ResourceWidgetData == nullptr)
	{
		// 테이블 자료 문제
		return nullptr;
	}

	const FString ResourcePath = gTableMng.GetPath(EMS_TableDataType::BasePathBPFile, ResourceWidgetData->Path_File, true);

	const TObjectPtr<UMS_Widget> ResultWidget = bManaged ? CreateWidget_Internal_Managing(ResourcePath) : CreateWidget_Internal_NotManaging(ResourcePath);

	if(ResultWidget == nullptr)
	{
		return nullptr;
	}

	FMS_ResourceWidgetInfo WidgetInfo;
	WidgetInfo.TypeName = ResourceWidgetData->TypeName;
	WidgetInfo.File = ResourcePath;
	WidgetInfo.zOrder = ResourceWidgetData->zOrder;
	//WidgetInfo.ExclusiveGroup = static_cast<EMS_ExclusiveGroup>(ResourceWidgetData->ExclusiveGroup);
	WidgetInfo.NotRender3D = ResourceWidgetData->NotRender3D;

	ResultWidget->SetResourceWidgetInfo(WidgetInfo);
	ResultWidget->InitWidget(aTypeName, bManaged, bAttachToRoot);

	return ResultWidget;
}

TObjectPtr<UMS_Widget> UMS_WidgetManager::CreateWidget_Internal_Managing(const FString& aPath)
{
	static FString SubName = TEXT("Create Widget");

	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);
	
	const TObjectPtr<UClass> WidgetClass = Cast<UClass>(LoadObjectFromFile(GEngine->AssetManager.Get()->GetStreamableManager(), aPath, FMS_LoadResourceDelegate::CreateUObject(this, &UMS_WidgetManager::LoadComplete)));
	if(WidgetClass == nullptr)
	{
		return nullptr;
	}

	return CreateWidget<UMS_Widget>(World, WidgetClass);
}

TObjectPtr<UMS_Widget> UMS_WidgetManager::CreateWidget_Internal_NotManaging(const FString& aPath) const
{
	static FString SubName = TEXT("Create Widget");
	const FString ClassName = aPath + TEXT("_C");
	
	const TObjectPtr<UClass> WidgetClass = Cast<UClass>(LoadObjectFromFile(GEngine->AssetManager.Get()->GetStreamableManager(), ClassName));
	const TObjectPtr<UWorld> World = GetWorld();
	
	if(World != nullptr && World->bIsTearingDown == false)
	{
		if(const TObjectPtr<UMS_Widget> Widget = CreateWidget<UMS_Widget>(World, WidgetClass))
		{
			return Widget;
		}
	}
	
	return nullptr;
}

void UMS_WidgetManager::LoadComplete(const FString& aTableName, TObjectPtr<UObject> aWidgetData)
{
	
}

UMS_WidgetManager* UMS_WidgetManager::GetInstance()
{
	return WidgetManager;
}
