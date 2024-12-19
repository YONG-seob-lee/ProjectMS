// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ItemUnit.h"

#include "MS_Actor.generated.h"

UCLASS()
class PROJECTMS_API AMS_Actor : public AActor
{
	GENERATED_BODY()

public:
	AMS_Actor();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void Create(const FString& aLabelName);
	
	void Initialize();
	void Finalize();
	
	FORCEINLINE void SetOwnerUnitBase(const TObjectPtr<UObject>& aOwner) { UnitOwner = aOwner; }
	FORCEINLINE TWeakObjectPtr<UObject> GetOwnerUnitBase() const { return UnitOwner; }

private:
	// UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// TObjectPtr<class UStaticMeshComponent> StaticMeshComponent = nullptr;
	
	// UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// TObjectPtr<class USphereComponent> TestSphere = nullptr;
	
	TWeakObjectPtr<UObject> UnitOwner = nullptr;
};
