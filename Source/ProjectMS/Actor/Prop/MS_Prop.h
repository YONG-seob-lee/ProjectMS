#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Environment/MS_LevelPropDatas.h"
#include "MS_Prop.generated.h"

UCLASS()
class PROJECTMS_API AMS_Prop : public AActor
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
	class UMeshComponent* GetMeshComponent() const { return MeshComponent; }

	TArray<class UMS_GridBoxComponent*> GetGridBoxComponents() const { return GridBoxComponents; }

	
	// Zone Data :: Setter
	virtual void SetZoneData(TWeakObjectPtr<class AMS_Zone> aOwnerZone, const FIntVector2& aZoneGridPosition);

	
protected:
	// Property
	UPROPERTY(EditDefaultsOnly)
	EMS_PropType PropType;
	
	UPROPERTY(EditDefaultsOnly)
	int32 TableIndex;

	
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_GridBoxComponent*> GridBoxComponents;

	
	// Zone Data
	UPROPERTY()
	TWeakObjectPtr<class AMS_Zone> OwnerZone;

	UPROPERTY()
	FIntVector2 ZoneGridPosition;
};
