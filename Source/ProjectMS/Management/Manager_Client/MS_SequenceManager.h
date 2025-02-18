// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "MS_ManagerBase.h"
#include "MS_SequenceManager.generated.h"

UENUM()
enum class EMS_SequenceType
{
	None = 0,
	Truck,
	Entrance,
};

namespace SequencePath
{
	const FString Truck = TEXT("/Game/Blueprints/Sequence/InToTruckSequence");
	const FString Entrance = TEXT("/Game/Blueprints/Sequence/DuckEntrance");
}
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

	void PlaySequence(EMS_SequenceType SequenceType);
	
private:
	TObjectPtr<class ULevelSequence> LoadSequence(EMS_SequenceType SequenceType) const;
	
	void OnSignatureChangedEvent();
	
	UFUNCTION()
	void OnFinishedSequence();

	UPROPERTY()
	ALevelSequenceActor* SequenceActor = nullptr;






	
public:
	inline static TObjectPtr<UMS_SequenceManager> SequenceManager = nullptr;
	static UMS_SequenceManager* GetInstance();
	
#define gSequenceMng (*UMS_SequenceManager::GetInstance())
};
