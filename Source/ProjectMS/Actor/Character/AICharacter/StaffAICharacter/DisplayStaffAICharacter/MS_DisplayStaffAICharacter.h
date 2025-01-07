#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "MS_DisplayStaffAICharacter.generated.h"

UCLASS() class PROJECTMS_API AMS_DisplayStaffAICharacter : public AMS_StaffAICharacter
{
	GENERATED_BODY()
	
public:
	AMS_DisplayStaffAICharacter();

	virtual UClass* GetLoadingStorageType() override;
	virtual UClass* GetUnloadingStorageType() override;
};
