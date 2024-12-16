#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Prop_Floor.generated.h"


UCLASS()
class PROJECTMS_API AMS_Prop_Floor : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Prop_Floor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetZoneData(TWeakObjectPtr<class AMS_Zone> aOwnerZone, const FIntVector2& aZoneGridPosition) override;

protected:
	// Component
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> WidgetComponent_ShowGridNum;
#endif
};
