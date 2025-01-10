// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "MS_SoundManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SoundManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_SoundManager();

private:
	UPROPERTY(EditAnywhere) TObjectPtr<class USoundMix> SoundMix = nullptr; 
};
