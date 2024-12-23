#include "MS_MenuElementCacheTable.h"

#include "Widget/ListViewElement/ElementData/MS_MenuElementData.h"

void UMS_MenuElementCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::MenuElement, MenuElements);
}

void UMS_MenuElementCacheTable::Finalize()
{
	Super::Finalize();
}

void UMS_MenuElementCacheTable::GetMenuData(TArray<TObjectPtr<UMS_MenuElementData>>& aMenuElements)
{
	aMenuElements.Empty();

	for(int32 i = 0 ; i <MenuElements.Num(); i++)
	{
		aMenuElements.Emplace(MS_NewObject<UMS_MenuElementData>());
		aMenuElements[i]->SetElementName(MenuElements[i + 1]->ElementName);
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, MenuElements[i + 1]->ImagePath);
		if(UTexture2D* IconImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			aMenuElements[i]->SetImage(IconImage);
		}
	}
}