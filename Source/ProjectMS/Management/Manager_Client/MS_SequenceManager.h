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
	OpenDoorTown,
	CloseDoorTown,
	OpenDoorMarket,
	CloseDoorMarket,
};

namespace SequencePath
{
	// Town
	const FString OpenDoor_Town1 = TEXT("/Game/Blueprints/Sequence/Town/DoorOpenSequence_Stage01");
	const FString OpenDoor_Town2 = TEXT("/Game/Blueprints/Sequence/Town/DoorOpenSequence_Stage02");
	const FString OpenDoor_Town3 = TEXT("/Game/Blueprints/Sequence/Town/DoorOpenSequence_Stage03");
	const FString CloseDoor_Town1 = TEXT("/Game/Blueprints/Sequence/Town/DoorCloseSequence_Stage01");
	const FString CloseDoor_Town2 = TEXT("/Game/Blueprints/Sequence/Town/DoorCloseSequence_Stage02");
	const FString CloseDoor_Town3 = TEXT("/Game/Blueprints/Sequence/Town/DoorCloseSequence_Stage03");
	
	// Market
	const FString Truck = TEXT("/Game/Blueprints/Sequence/Market/InToTruckSequence");
	const FString Entrance = TEXT("/Game/Blueprints/Sequence/Market/DuckEntrance");
	const FString OpenDoor_Market = TEXT("/Game/Blueprints/Sequence/Market/DoorOpenSequence");
	const FString CloseDoor_Market = TEXT("/Game/Blueprints/Sequence/Market/DoorCloseSequence");
}

struct FMS_SequencePlayParameter
{
public:
	FMS_SequencePlayParameter() { bCheckedSequencePlay = true; bHideWidget = true; bSetBlendCamera = true; OnFinishedSequenceCallback = nullptr; }
	FMS_SequencePlayParameter(bool _bCheckedSequencePlay, bool _bSetBlendCamera,  bool _bHideWidget, TFunction<void()> _OnFinishedSequenceCallback = nullptr) : bCheckedSequencePlay(_bCheckedSequencePlay), bSetBlendCamera(_bSetBlendCamera), bHideWidget(_bHideWidget), OnFinishedSequenceCallback(_OnFinishedSequenceCallback) {}
	FMS_SequencePlayParameter(bool _bCheckedSequencePlay, bool _bSetBlendCamera, bool _bMute,  bool _bHideWidget, TFunction<void()> _OnFinishedSequenceCallback = nullptr) : bCheckedSequencePlay(_bCheckedSequencePlay), bSetBlendCamera(_bSetBlendCamera), bHideWidget(_bHideWidget), bMute(_bMute), OnFinishedSequenceCallback(_OnFinishedSequenceCallback) {}
	bool bCheckedSequencePlay = true;
	bool bSetBlendCamera = true;
	bool bHideWidget = true;
	bool bMute = true;
	TFunction<void()> OnFinishedSequenceCallback = nullptr;
};
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

	void PlaySequence(EMS_SequenceType SequenceType, const FMS_SequencePlayParameter& Parameter = FMS_SequencePlayParameter());
	void StopSequence();
	bool IsPlayingSequence() const;

private:
	TObjectPtr<class ULevelSequence> LoadSequence(EMS_SequenceType SequenceType) const;
	
	void OnSignatureChangedEvent();
	
	UFUNCTION()
	void OnFinishedSequence();

	FMS_SequencePlayParameter RequestParameter = FMS_SequencePlayParameter();
	float MasterVolume = 0.f;
	float SequenceVolume = 0.f;
	
	UPROPERTY()
	ALevelSequenceActor* SequenceActor = nullptr;

	TFunction<void()> OnFinishedSequenceCallback = nullptr;




	
public:
	inline static TObjectPtr<UMS_SequenceManager> SequenceManager = nullptr;
	static UMS_SequenceManager* GetInstance();
	
#define gSequenceMng (*UMS_SequenceManager::GetInstance())
};
