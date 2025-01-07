#include "Actor/Character/AICharacter/StaffAICharacter/DisplayStaffAICharacter/MS_DisplayStaffAICharacter.h"

#include "AI/AIController/StaffAIController/DisplayStaffAIController/MS_DisplayStaffAIController.h"
#include "Actor/Storage/Display/MS_DisplayStorage.h"
#include "Actor/Storage/Shelf/MS_ShelfStorage.h"

AMS_DisplayStaffAICharacter::AMS_DisplayStaffAICharacter()
{
	AIControllerClass = AMS_DisplayStaffAIController::StaticClass();
}

UClass* AMS_DisplayStaffAICharacter::GetLoadingStorageType()
{
	return AMS_DisplayStorage::StaticClass();
}

UClass* AMS_DisplayStaffAICharacter::GetUnloadingStorageType()
{
	return AMS_ShelfStorage::StaticClass();
}
