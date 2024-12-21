#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "Environment/MS_LevelPropDatas.h"
#include "MS_Prop.generated.h"

UCLASS()
class PROJECTMS_API AMS_Prop : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_Prop();

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
	// Property :: Getter
	EMS_PropType GetPropType() const { return PropType; }
	
	int32 GetTableIndex() const { return TableIndex; }


	// Component :: Getter
	TArray<class UMS_PropSpaceComponent*> GetPropSpaceComponents() const { return PropSpaceComponents; }
	
	TArray<class UMS_PropSpaceComponent*> GetPropPurposeSpaceComponents(EMS_PurposeType aPropPurposeSpace) const;

	
	// Zone Data :: Setter
	virtual void SetZoneData(TWeakObjectPtr<class AMS_Zone> aOwnerZone, const FVector& aPropCenterLocationInZone);

	
protected:
	// Property
	UPROPERTY(EditDefaultsOnly)
	EMS_PropType PropType;
	
	UPROPERTY(EditDefaultsOnly)
	int32 TableIndex;

	
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_PropSpaceComponent*> PropSpaceComponents;
	
	// Zone Data
	UPROPERTY()
	TWeakObjectPtr<class AMS_Zone> OwnerZone;

	UPROPERTY()
	FVector PropCenterLocationInZone;
};
