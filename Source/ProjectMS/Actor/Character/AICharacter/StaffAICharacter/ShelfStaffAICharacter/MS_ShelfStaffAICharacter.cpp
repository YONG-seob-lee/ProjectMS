#include "Actor/Character/AICharacter/StaffAICharacter/ShelfStaffAICharacter/MS_ShelfStaffAICharacter.h"

#include "AI/AIController/StaffAIController/ShelfStaffAIController/MS_ShelfStaffAIController.h"
#include "Actor/Storage/Shelf/MS_ShelfStorage.h"
#include "Actor/Storage/Pallet/MS_PalletStorage.h"

AMS_ShelfStaffAICharacter::AMS_ShelfStaffAICharacter()
{
	AIControllerClass = AMS_ShelfStaffAIController::StaticClass();
}

UClass* AMS_ShelfStaffAICharacter::GetLoadingStorageType()
{
	return AMS_ShelfStorage::StaticClass();
}

UClass* AMS_ShelfStaffAICharacter::GetUnloadingStorageType()
{
	return AMS_PalletStorage::StaticClass();
}
