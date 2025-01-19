#include "AI/Debug/MS_DebugControlStorageItemUI.h"

#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/Button.h"

#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "CoreClass/Controller/MS_PlayerController.h"
#include "Manager_Client/MS_InputManager.h"
#include "Management/MS_ManagementClient.h"
#include "Management/Manager_Client/MS_PlayerCameraManager.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"
#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"
#include "Management/Manager_Both/MS_TableManager.h"
#include "Data/Table/RowBase/MS_ItemData.h"



UMS_DebugControlStorageItemUI::UMS_DebugControlStorageItemUI(const FObjectInitializer& aObjectInitializer) : Super(aObjectInitializer)
{
	bIsFocusable = true;
}

void UMS_DebugControlStorageItemUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Visible);
	PlayerController = Cast<AMS_PlayerController>(GetOwningPlayer());

    ItemNameEditableTextArray.Add(Slot1ItemNameEditableText);
    ItemNameEditableTextArray.Add(Slot2ItemNameEditableText);
    ItemNameEditableTextArray.Add(Slot3ItemNameEditableText);
    ItemNameEditableTextArray.Add(Slot4ItemNameEditableText);
    QuantityEditableTextArray.Add(Slot1ItemQuantity);
    QuantityEditableTextArray.Add(Slot2ItemQuantity);
    QuantityEditableTextArray.Add(Slot3ItemQuantity);
    QuantityEditableTextArray.Add(Slot4ItemQuantity);
    CapacityEditableTextArray.Add(Slot1ItemCapacity);
    CapacityEditableTextArray.Add(Slot2ItemCapacity);
    CapacityEditableTextArray.Add(Slot3ItemCapacity);
    CapacityEditableTextArray.Add(Slot4ItemCapacity);

    AssignStoragePropertiesButton->OnClicked.AddDynamic(this, &UMS_DebugControlStorageItemUI::OnAssignStoragePropertiesButtonClicked);
    ChangeBundleStaticMeshButton->OnClicked.AddDynamic(this, &UMS_DebugControlStorageItemUI::OnChangeBundleStaticMeshButtonClicked);
    ChangeBoxStaticMeshButton->OnClicked.AddDynamic(this, &UMS_DebugControlStorageItemUI::OnChangeBoxStaticMeshButtonClicked);
}

FReply UMS_DebugControlStorageItemUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == false)
    {
        return FReply::Unhandled();
    }

    AMS_ViewCamera* ViewCamera = Cast<AMS_ViewCamera>(Cast<AMS_PlayerCameraManager>(PlayerController->PlayerCameraManager)->ViewCamera);

    FVector CameraLocation = ViewCamera->CameraComponent->GetComponentLocation();
    FVector CameraForwardVector = ViewCamera->CameraComponent->GetForwardVector();

    FVector LineTraceStartLocation = CameraLocation;
    FVector LineTraceEndLocation = LineTraceStartLocation + (CameraForwardVector * 10000.0f);

    FHitResult HitResult;

    DrawDebugLine(GetWorld(), LineTraceStartLocation, LineTraceEndLocation, FColor::Cyan, false, 5.0f, 0, 2.0f);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStartLocation, LineTraceEndLocation, ECC_Visibility))
    {
        Storage = Cast<AMS_Storage>(HitResult.GetActor());
        if (Storage != nullptr)
        {
            StorageTextBlock->SetText(FText::FromString(Storage->GetName()));

            for (auto EditableText : ItemNameEditableTextArray)
            {
                EditableText->SetText(FText());
            }
            for (auto EditableText : QuantityEditableTextArray)
            {
                EditableText->SetText(FText());
            }
            for (auto EditableText : CapacityEditableTextArray)
            {
                EditableText->SetText(FText());
            }

            for (int i = 0; i < Storage->SlotComponentArray.Num(); i++)
            {
                ItemNameEditableTextArray[i]->SetText(FText::FromName(Storage->SlotComponentArray[i]->StuffRowName));
                QuantityEditableTextArray[i]->SetText(FText::AsNumber(Storage->SlotComponentArray[i]->StockQuantity));
                CapacityEditableTextArray[i]->SetText(FText::AsNumber(Storage->SlotComponentArray[i]->StockCapacity));
            }
        }
    }

    return FReply::Unhandled();
}

void UMS_DebugControlStorageItemUI::AdjustAllStorageItem(const FString& aItemName)
{
	//if (GetWorld() == false)
	//{
	//	return;
	//}

	//TArray<AActor*> StorageActorArray = {};
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Storage::StaticClass(), StorageActorArray);

	//for (AActor* StorageActor : StorageActorArray)
	//{
	//	AMS_Storage* Storage = Cast<AMS_Storage>(StorageActor);
	//	for (int i = 0; i < Storage->SlotComponentArray.Num(); i++)
	//	{

	//	}
	//}
}

void UMS_DebugControlStorageItemUI::OnAssignStoragePropertiesButtonClicked()
{
    if (Storage == nullptr)
    {
        return;
    }

    TObjectPtr<UDataTable> ItemData = gTableMng.GetTableData(EMS_TableDataType::ItemData);
    MS_CHECK(ItemData);

    for (int i = 0; i < Storage->SlotComponentArray.Num(); i++)
    {
        Storage->SlotComponentArray[i]->StuffRowName = FName(ItemNameEditableTextArray[i]->GetText().ToString());

        int Quantity = FCString::Atoi(*QuantityEditableTextArray[i]->GetText().ToString());
        Storage->SlotComponentArray[i]->StockQuantity = Quantity;
        if (Quantity == 0)
        {
            Storage->SlotComponentArray[i]->SetStaticMesh(nullptr);
        }
        //else
        //{
        //    FMS_ItemData* ItemDataTableRow = ItemData->FindRow<FMS_ItemData>(Storage->SlotComponentArray[i]->StuffRowName, TEXT(""));
        //    MS_CHECK(ItemDataTableRow);

        //    if (SlotStaticMeshSwitch == false)
        //    {
        //        Storage->SlotComponentArray[i]->SetStaticMesh(ItemDataTableRow->StuffBoxStaticMesh);
        //    }
        //    else
        //    {
        //        Storage->SlotComponentArray[i]->SetStaticMesh(ItemDataTableRow->StuffBundleStaticMesh);
        //    }
        //}

        Storage->SlotComponentArray[i]->StockCapacity = FCString::Atoi(*CapacityEditableTextArray[i]->GetText().ToString());
    }
}

void UMS_DebugControlStorageItemUI::OnChangeBoxStaticMeshButtonClicked()
{
    SlotStaticMeshSwitch = false;
}

void UMS_DebugControlStorageItemUI::OnChangeBundleStaticMeshButtonClicked()
{
    SlotStaticMeshSwitch = true;
}
