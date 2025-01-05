// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "MS_InteractionManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectActorDelegate, AActor*, aSelectedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnselectActorDelegate, AActor*, aUnselectedActor);

UCLASS()
class PROJECTMS_API UMS_InteractionManager : public UMS_ManagerBase
{
	GENERATED_BODY()

public:
	UMS_InteractionManager();
	
	static UMS_InteractionManager* GetInstance();
	
	void SelectActor(TWeakObjectPtr<AActor> aSelectedActor);
	void UnselectActor();

	TWeakObjectPtr<AActor> GetSelectedActor() const { return SelectedActor; }

	template<typename T>
	TWeakObjectPtr<T> GetSelectedActor() const { return Cast<T>(SelectedActor); }
	
private:
	inline static TObjectPtr<UMS_InteractionManager> InteractionManager = nullptr;

	UPROPERTY()
	TWeakObjectPtr<AActor> SelectedActor;

public:
	UPROPERTY()
	FOnSelectActorDelegate OnSelectActorDelegate;

	UPROPERTY()
	FOnUnselectActorDelegate OnUnselectActorDelegate;

#define gInteractionMng (*UMS_InteractionManager::GetInstance())
};
