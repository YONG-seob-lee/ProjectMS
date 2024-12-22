#include "Actor/Character/AICharacter/StaffAICharacter/ShelfStaffAICharacter/MS_ShelfStaffAICharacter.h"

#include "AI/AIController/StaffAIController/ShelfStaffAIController/MS_ShelfStaffAIController.h"

AMS_ShelfStaffAICharacter::AMS_ShelfStaffAICharacter()
{
	AIControllerClass = AMS_ShelfStaffAIController::StaticClass();
}
