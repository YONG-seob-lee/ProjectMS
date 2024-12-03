// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MS_CharacterBase.generated.h"

USTRUCT(BlueprintType)
struct FMS_CharacterLodValues
{
	GENERATED_BODY()
	FMS_CharacterLodValues() {}

public:
	UPROPERTY(Category = "FMS_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 CullDistance = 0;

	UPROPERTY(Category = "FMS_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 OutLineCullDistance = 0;

	// not used
	UPROPERTY(Category = "FMS_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) 
	int32 AnimMaxDistanceFactor = 0;

	UPROPERTY(Category = "FMS_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<float> AnimThresholdTable;

	UPROPERTY(Category = "FMS_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 BaseNonRenderedUpdateRate = 0;

	float CullDistanceScale = 1.0f;
	float OutLineCullDistanceScale = 1.0f;
	bool  bVisibleOutLine = true;
};

UCLASS()
class PROJECTMS_API AMS_CharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	AMS_CharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent);
	
	FORCEINLINE TObjectPtr<USceneComponent> GetCharacterRootComponent() const { return RootComponent; }
	
	void SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine);

private:
	
	UPROPERTY(Category = AITT_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMS_CharacterLodValues LodValues = FMS_CharacterLodValues();
};
