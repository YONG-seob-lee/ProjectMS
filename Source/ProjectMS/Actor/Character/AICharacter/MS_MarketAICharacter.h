// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_AICharacter.h"
#include "Component/Actor/MS_AIParameterComponent.h"
#include "MathUtility/MS_MathUtility.h"
#include "Widget/Dialog/SpeechBubble/MS_SpeechBubbleWidget.h"
#include "MS_MarketAICharacter.generated.h"


DECLARE_DELEGATE_OneParam(FMS_OnReachPathLocationDelegate, const FVector2D&);

UCLASS()
class PROJECTMS_API AMS_MarketAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()

public:
	AMS_MarketAICharacter();

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;


	EMS_Direction GetWalkingDirection() const { return WalkingDirection; }
	const FVector2D& GetPathLocation() const { return PathLocation; }
	
	void SetWalkingDirectionAndPathLocation(EMS_Direction aWalkingDirection, FVector2D aPathLocation, bool aStopInPathLocation);

	void SetRotationByWalkingDirection(EMS_Direction aWalkingDirection);

private:
	void UpdateLocation(float aDeltaTime);
	void UpdateRotation(float aDeltaTime);

	bool IsRotationComplete() const;

public:
	// Slot Datas
	virtual void OnChangeCurrentSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas);

	// Equipment
	void SpawnAllEquipment();
	
	void Equip(const FName& aEquipmentName);
	void UnEquip();

	UFUNCTION()
	void OnChangeAnimationInAction(bool bInAction);
	
	void UpdateShowEquipment();

	// Skin
	void SetSkin(const FName& aCapName, const FName& aTopName);

	// Chatting
	void ShowChatting(EMS_ChattingType ChattingType) const;
	void ShowImage(EMS_SpeechImageType SpeechImageType) const;

	FORCEINLINE void ResetChatting() { bIsChatting = false;}
	FORCEINLINE bool IsChattingBefore() const { return bIsChatting; }
	
protected:
	// Component
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> SkinCapMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> SkinTopMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_MovingBoxComponent*> MovingBoxComponents;

	// Skin
	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<class USkeletalMesh>> SkinCaps;

	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<class USkeletalMesh>> SkinTops;
	
	// Property
	UPROPERTY(EditAnywhere)
	float DuckVelocity = 100.f;

	UPROPERTY(EditAnywhere)
	float DuckRotateVelocity = 180.f;	// 1칸 이동할 시간에 90도는 돌 수 있어야 함.
	
	// Walking Progress
	UPROPERTY()
	EMS_Direction WalkingDirection = EMS_Direction::None;
	
	UPROPERTY()
	FVector2D PathLocation;

	UPROPERTY()
	FVector2D PreviousPathLocation;

	UPROPERTY()
	bool bStopInPathLocation;

	// Equipment
	UPROPERTY(EditAnywhere)
	TMap<FName, TSubclassOf<class AMS_Equipment>> EquipmentClasses;

	UPROPERTY()
	TMap<FName, TObjectPtr<class AMS_Equipment>> Equipments;
	
	UPROPERTY()
	FName CurrentEquipmentName = {};

	UPROPERTY()
	bool bShowEquipment = false;
	
	// Chatting
	bool bIsChatting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> WidgetComponent = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_AIParameterComponent> AIParameterComponent = nullptr;
	
public:
	// Walking Progress
	FMS_OnReachPathLocationDelegate OnReachPathLocationDelegate;
};
