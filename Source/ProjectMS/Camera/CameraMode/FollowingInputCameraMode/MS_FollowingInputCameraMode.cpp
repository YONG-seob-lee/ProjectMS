#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "Management/MS_PlayerCameraManager.h"
#include "CoreClass/Controller/MS_PlayerController.h"

#include "Management/MS_TableManager.h"
#include "Data/Table/RowBase/MS_InputActionData.h"

UMS_FollowingInputCameraMode::UMS_FollowingInputCameraMode()
{
}

void UMS_FollowingInputCameraMode::ActivateMode()
{
	Super::ActivateMode();

	AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(CameraManager->PCOwner);
	MS_CHECK(PlayerController);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	MS_CHECK(EnhancedInputComponent);

	TObjectPtr<UMS_TableManager> TableManagerInst = PlayerController->GetTableManager();
	MS_CHECK(TableManagerInst);

	TMap<FName, uint8*> InputDataMap = {};
	TableManagerInst->GetRowDataMap(EMS_TableDataType::InputActionData, InputDataMap);

	if (InputDataMap.Num() == 0)
	{
		MS_CHECK(nullptr);
	}

	uint8** DollyInIndex = InputDataMap.Find(FName("DollyIn"));
	FMS_InputActionData* DollyInActionData = reinterpret_cast<FMS_InputActionData*>(*DollyInIndex);
	EnhancedInputComponent->BindAction(DollyInActionData->InputAction, ETriggerEvent::Triggered, CameraManager, TEXT("DollyIn"));

	uint8** DollyOutIndex = InputDataMap.Find(FName("DollyOut"));
	FMS_InputActionData* DollyOutActionData = reinterpret_cast<FMS_InputActionData*>(*DollyOutIndex);
	EnhancedInputComponent->BindAction(DollyOutActionData->InputAction, ETriggerEvent::Triggered, CameraManager, TEXT("DollyOut"));

	uint8** TruckLeftIndex = InputDataMap.Find(FName("TruckLeft"));
	FMS_InputActionData* TruckLeftActionData = reinterpret_cast<FMS_InputActionData*>(*TruckLeftIndex);
	EnhancedInputComponent->BindAction(TruckLeftActionData->InputAction, ETriggerEvent::Triggered, CameraManager, TEXT("TruckLeft"));

	uint8** TruckRightIndex = InputDataMap.Find(FName("TruckRight"));
	FMS_InputActionData* TruckRightActionData = reinterpret_cast<FMS_InputActionData*>(*TruckRightIndex);
	EnhancedInputComponent->BindAction(TruckRightActionData->InputAction, ETriggerEvent::Triggered, CameraManager, TEXT("TruckRight"));


#if PLATFORM_WINDOWS || PLATFORM_MAC

#elif PLATFORM_ANDROID || PLATFORM_IOS

#endif
}

void UMS_FollowingInputCameraMode::DeactivateMode()
{
	Super::DeactivateMode();

	AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(CameraManager->PCOwner);
	MS_CHECK(PlayerController);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	MS_CHECK(EnhancedInputComponent);

	EnhancedInputComponent->ClearActionBindings();

#if PLATFORM_WINDOWS || PLATFORM_MAC

#elif PLATFORM_ANDROID || PLATFORM_IOS

#endif
}
