// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Market.generated.h"

UCLASS()
class PROJECTMS_API AMS_Market : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Market(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual bool HasInteractionComponent() override;
	virtual void OnPressDownEvent() override;
	virtual void OnPressUpEvent() override;
	virtual void LaunchEvent() override;

private:
	bool CheckTutorialFinished();
	void PlayTutorial() const;

	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMS_InteractionComponent> InteractionComponent = nullptr;
};
