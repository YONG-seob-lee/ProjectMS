// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageCacheTable.h"

#include "Widget/ListViewElement/ElementData/MS_ConstructItemElement.h"

void UMS_StorageCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::Storage, StorageDatas);
}

void UMS_StorageCacheTable::Finalize()
{
	Super::Finalize();
}

void UMS_StorageCacheTable::GetStorageData(TArray<TObjectPtr<UMS_ConstructItemElement>>& aConstructArray)
{
	aConstructArray.Empty();

	for(const auto& StorageData : StorageDatas)
	{
		TObjectPtr<UMS_ConstructItemElement> ConstructItem = MS_NewObject<UMS_ConstructItemElement>();
		ConstructItem->SetElementName(StorageData.Value->StandName.ToString());
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StorageData.Value->ImagePath); 
		if(UTexture2D* ImageImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			ConstructItem->SetImage(ImageImage);
		}
		aConstructArray.Emplace(ConstructItem);
	}
}
