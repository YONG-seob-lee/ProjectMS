// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "MS_ManagerBase.h"
#include "MS_SequenceManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SequenceManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_SequenceManager();
	
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;
	virtual void BeginPlay() override;

	void PlaySequence();
	
private:
	void OnSignatureChangedEvent();
	
	UFUNCTION()
	void OnFinishedSequence();

	UPROPERTY()
	TObjectPtr<class ULevelSequence> Sequence = nullptr;

	UPROPERTY()
	ALevelSequenceActor* SequenceActor = nullptr;
	
public:
	inline static TObjectPtr<UMS_SequenceManager> SequenceManager = nullptr;
	static UMS_SequenceManager* GetInstance();
	
#define gSequenceMng (*UMS_SequenceManager::GetInstance())
};
