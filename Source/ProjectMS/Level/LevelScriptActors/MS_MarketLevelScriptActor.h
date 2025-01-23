// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "Level/MS_ConstructibleLevelScriptActorBase.h"
#include "ScriptActorComponent/MS_UnitChattingCollectComponent.h"
#include "MS_MarketLevelScriptActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_MarketLevelScriptActor : public AMS_ConstructibleLevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_MarketLevelScriptActor();
	virtual void Tick(float DeltaTime) override;

	void GetUnitsHandle(TMap<MS_Handle, bool>& aUnitsHandle) const;
	void GetUnitChatting(MS_Handle aUnitHandle, TArray<FMS_ChattingParameter>& aParameters) const;
	void GetAllChattingCollection(TArray<FMS_ChattingParameter>& aChattingCollection) const;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
public:

private:
	UPROPERTY()
	TObjectPtr<class UMS_UnitChattingCollectComponent> ChattingCollectComponent = nullptr;
};
