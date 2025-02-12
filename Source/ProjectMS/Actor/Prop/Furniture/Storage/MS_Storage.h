#pragma once

#include "CoreMinimal.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "MS_Storage.generated.h"


enum class EMS_ModeState : uint8;

UCLASS()
class PROJECTMS_API AMS_Storage : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_Storage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;


public:
	virtual void OpenManagementWidget(const FVector2D& aClickPosition, EMS_ModeState aModeState) override;
	virtual void CloseManagementWidget(EMS_ModeState aModeState) override;
};