#include "Actor/Character/AICharacter/StaffAICharacter/DisplayStaffAICharacter/MS_DisplayStaffAICharacter.h"

#include "AI/AIController/StaffAIController/DisplayStaffAIController/MS_DisplayStaffAIController.h"

AMS_DisplayStaffAICharacter::AMS_DisplayStaffAICharacter()
{
	AIControllerClass = AMS_DisplayStaffAIController::StaticClass();
}
