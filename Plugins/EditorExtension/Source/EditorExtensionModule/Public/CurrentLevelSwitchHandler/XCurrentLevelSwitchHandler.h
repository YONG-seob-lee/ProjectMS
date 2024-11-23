#pragma once

#include "CoreMinimal.h"

class UXCurrentLevelSwitchHandler
{
public:
	UXCurrentLevelSwitchHandler();
	void Activate();
	void Deactivate();
	void OnNewCurrentLevel();
};