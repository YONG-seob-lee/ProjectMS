#include "MS_GameMode.h"

#include "CoreClass/Controller/MS_PlayerController.h"

AMS_GameMode::AMS_GameMode()
{
	PlayerControllerClass = AMS_PlayerController::StaticClass();
}
