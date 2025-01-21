#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Floor.generated.h"


UCLASS()
class PROJECTMS_API AMS_Floor : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Floor(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetZoneData(TWeakObjectPtr<class AMS_Zone> aOwnerZone, const FIntVector2& aGridPosition) override;
	
	virtual void SetMaterial(const FName& MaterialKey);

protected:
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMeshComponent* MeshComponent;

	// Material
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, TObjectPtr<class UMaterialInterface>> Materials;

	
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> WidgetComponent_ShowGridNum;
#endif
};
