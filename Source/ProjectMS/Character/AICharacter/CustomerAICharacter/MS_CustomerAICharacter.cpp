#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Equipment/MS_ItemEquipment.h"
#include "Table/Caches/MS_ItemCacheTable.h"


AMS_CustomerAICharacter::AMS_CustomerAICharacter()
{
	AIControllerClass = AMS_CustomerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_CustomerAICharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_CustomerAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	if(ItemTable == nullptr)
	{
		return;
	}

	TMap<int32, FMS_ItemData*> ItemDatas = {};
	ItemTable->GetItems(ItemDatas);

	for(const auto& ItemData : ItemDatas)
	{
		if(UStaticMesh* ItemMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass()
			, nullptr, *gTableMng.GetPath(EMS_TableDataType::BasePathMeshFile, ItemData.Value->MeshPath))))
		{
			Items.Emplace(ItemData.Key, ItemMesh);
		}
	}
}

void AMS_CustomerAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_CustomerAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_CustomerAICharacter::PostInitialize(MS_Handle aUnitHandle)
{
	Super::PostInitialize(aUnitHandle);

	// 오리 색깔 교체.
	if(UMaterialInterface* MaterialInterface = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *gTableMng.GetPath(EMS_TableDataType::BasePathBPFile, FMath::RandRange(DuckBodyColor::Pink, DuckBodyColor::White)))))
	{
		GetMesh()->SetMaterial(0, MaterialInterface);
	}
}

void AMS_CustomerAICharacter::PickUp(int32 ItemTableId)
{
	if(PickUpSockets.Find(static_cast<int32>(EMS_PickUpSocketType::Head)) == nullptr)
	{
		if(const TObjectPtr<UStaticMesh>* StaticMesh = Items.Find(ItemTableId))
		{
			if(AMS_ItemEquipment* ItemEquipment = GetWorld()->SpawnActor<AMS_ItemEquipment>(StaticLoadClass(UObject::StaticClass(), nullptr, *ItemEquipment::Path)))
			{
				ItemEquipment->SetMesh(StaticMesh);
				const USkeletalMeshSocket* EquipmentSocket = GetMesh()->GetSocketByName(SocketName::HeadItem);
				EquipmentSocket->AttachActor(ItemEquipment, GetMesh());
				PickUpSockets.Emplace(static_cast<int32>(EMS_PickUpSocketType::Head), ItemEquipment);
			}
		}
	}
	else
	{
		if(PickUpSockets.Find(static_cast<int32>(EMS_PickUpSocketType::RightHand)) == nullptr)
		{
			if(const TObjectPtr<UStaticMesh>* StaticMesh = Items.Find(ItemTableId))
			{
				if(AMS_ItemEquipment* ItemEquipment = GetWorld()->SpawnActor<AMS_ItemEquipment>(StaticLoadClass(UObject::StaticClass(), nullptr, *ItemEquipment::Path)))
				{
					ItemEquipment->SetMesh(StaticMesh);
					const USkeletalMeshSocket* EquipmentSocket = GetMesh()->GetSocketByName(SocketName::RightItem);
					EquipmentSocket->AttachActor(ItemEquipment, GetMesh());
					PickUpSockets.Emplace(static_cast<int32>(EMS_PickUpSocketType::RightHand), ItemEquipment);
				}
			}
		}
		else
		{
			if(PickUpSockets.Find(static_cast<int32>(EMS_PickUpSocketType::LeftHand)) == nullptr)
			{
				if(const TObjectPtr<UStaticMesh>* StaticMesh = Items.Find(ItemTableId))
				{
					if(AMS_ItemEquipment* ItemEquipment = GetWorld()->SpawnActor<AMS_ItemEquipment>(StaticLoadClass(UObject::StaticClass(), nullptr, *ItemEquipment::Path)))
					{
						ItemEquipment->SetMesh(StaticMesh);
						const USkeletalMeshSocket* EquipmentSocket = GetMesh()->GetSocketByName(SocketName::LeftItem);
						EquipmentSocket->AttachActor(ItemEquipment, GetMesh());
						PickUpSockets.Emplace(static_cast<int32>(EMS_PickUpSocketType::LeftHand), ItemEquipment);
					}
				}
			}
		}
	}
}

void AMS_CustomerAICharacter::ShowPickUp(bool bShow)
{
	for(const auto& PickUpItem : PickUpSockets)
	{
		PickUpItem.Value->ShowEquipment(bShow);
	}
}
