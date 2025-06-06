﻿#pragma once

#include "CoreMinimal.h"
#include "MS_ActorBase.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_Prop.generated.h"


DECLARE_DELEGATE_OneParam(FMS_CancelSelectedDelegate, TWeakObjectPtr<AMS_Prop>);

UCLASS()
class PROJECTMS_API AMS_Prop : public AMS_ActorBase
{
	GENERATED_BODY()

public:
	AMS_Prop(const FObjectInitializer& aObjectInitializer);

	virtual void PreInitializeComponents() override;

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	// Property :: Getter
	EMS_PropType GetPropType() const { return PropType; }
	
	int32 GetTableIndex() const { return TableIndex; }

	const FIntVector& GetGridNum() const { return GridNum; }
	
	FIntVector2 GetGridPosition() const;

	
	// Component :: Getter
	TArray<class UMeshComponent*> GetMeshComponents() const { return MeshComponents; }
	class UMeshComponent* GetMeshComponent(int32 aArrayIndex = 0) const;
	
	TArray<class UMS_PropSpaceComponent*> GetPropSpaceComponents() const { return PropSpaceComponents; }
	
	TArray<class UMS_PropSpaceComponent*> GetPropPurposeSpaceComponents(EMS_PurposeType aPropPurposeSpace) const;

	class UMS_PropSpaceComponent* GetPropSpaceComponentByRelativeLocation(const FVector& aRelativeLocation) const;

	void GetAllGridPositions(TArray<FIntVector2>& aOutGridPositions) const;

	virtual EMS_ZoneType GetConstructableZoneType() const;

	
	// Zone Data :: Setter
	virtual void SetZoneData(TWeakObjectPtr<class AMS_Zone> aOwnerZone);
	

	// Select
	virtual void OnSelectProp(EMS_ModeState aModeState);
	virtual void OnUnselectProp(EMS_ModeState aModeState);

	virtual TWeakObjectPtr<class UMS_Widget> OpenStatusWidget();
	virtual void CloseStatusWidget();

	
	// For Preview
	void InitializeWhenPreviewProp(AMS_Prop* aLinkedProp);
	
	TWeakObjectPtr<AMS_Prop> GetLinkedProp() const { return LinkedProp; }

	bool IsPreviewProp() const { return bIsPreviewProp; }

	// Arrangement Widget
	class UWidgetComponent* GetArrangementWidgetComponent() const;
	
	class UMS_ArrangementWidget* GetArrangementWidget() const;

	void ShowArrangementWidget(bool bShow) const;

	virtual void SetVisibility(bool bVisibility);

	
protected:
	UPROPERTY(EditAnywhere, Category=HISM)
	FName MeshName = {};

	UPROPERTY()
	int32 MeshIndex = 0;
	
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMeshComponent*> MeshComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_PropSpaceComponent*> PropSpaceComponents;
	
	// Property
	UPROPERTY(EditDefaultsOnly)
	EMS_PropType PropType;
	
	UPROPERTY(EditDefaultsOnly)
	int32 TableIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector GridNum;
	
	// Zone Data
	UPROPERTY()
	TWeakObjectPtr<class AMS_Zone> OwnerZone;

	// Management Widget
	UPROPERTY()
	TWeakObjectPtr<class UMS_Widget> StatusWidget;
	
	// Arrangement Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> ArrangementWidgetComponent;

	// For Preview
	UPROPERTY()
	bool bIsPreviewProp;
	
	TWeakObjectPtr<AMS_Prop> LinkedProp;

public:
	FMS_CancelSelectedDelegate CancelSelectedDelegate;
};
