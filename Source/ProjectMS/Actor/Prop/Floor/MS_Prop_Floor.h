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
};
