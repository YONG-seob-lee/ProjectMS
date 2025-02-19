#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Staff/MS_StaffActionWidget.h"


AMS_StaffAICharacter::AMS_StaffAICharacter()
{
	AIControllerClass = AMS_StaffAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_StaffAICharacter::ShowStaffStatusWidget(const FVector2D& _ClickPosition)
{
	if(UMS_Widget* StaffActionWidget = gWidgetMng.Create_Widget(UMS_StaffActionWidget::GetWidgetName(), false))
	{
		gWidgetMng.SetCustomPositionWidget(StaffActionWidget, _ClickPosition);
	}
}

void AMS_StaffAICharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_StaffAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_StaffAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_StaffAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}