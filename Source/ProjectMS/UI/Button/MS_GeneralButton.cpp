// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralButton.h"

#include "Components/Image.h"

namespace ImagePath
{
	const FString Setting = TEXT("/Game/UI/Image/Icon/SettingIcon.SettingIcon");
	const FString Menu = TEXT("/Game/UI/Image/Icon/MenuIcon.MenuIcon");
	const FString Schedule = TEXT("/Game/UI/Image/Icon/BoardIcon.BoardIcon");
	const FString Manage = TEXT("/Game/UI/Image/Icon/ManageIcon.ManageIcon");
	const FString OrderItem = TEXT("/Game/UI/Image/Icon/BuyItem.BuyItem");
	const FString CheckOrderItem = TEXT("/Game/UI/Image/Icon/CheckOrderItem.CheckOrderItem");
	const FString BuyFurniture = TEXT("/Game/UI/Image/Icon/BuyFurniture.BuyFurniture");
	const FString HireStaff = TEXT("/Game/UI/Image/Icon/HireStaffIcon.HireStaffIcon");
	const FString StaffManage = TEXT("/Game/UI/Image/Icon/StaffManageIcon.StaffManageIcon");
	const FString CustomerManage = TEXT("/Game/UI/Image/Icon/CustomerManageIcon.CustomerManageIcon");
	const FString SalesDetail = TEXT("/Game/UI/Image/Icon/SalesDetailIcon.SalesDetailIcon");
}

void UMS_GeneralButton::SetButtonType(EMS_GeneralButtonType aType)
{
	ButtonType = aType;
	switch(aType)
	{
	case EMS_GeneralButtonType::Setting:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Setting));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::Menu:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Menu));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::Schedule:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Schedule));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::Manage:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Manage));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::OrderItem:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::OrderItem));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::CheckOrderItem:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::CheckOrderItem));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::BuyFurniture:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::BuyFurniture));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::HireStaff:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::HireStaff));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::StaffManage:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::StaffManage));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::CustomerManage:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::CustomerManage));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::SalesDetail:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::SalesDetail));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	default:
		{
			CPP_Image->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
	}
}

void UMS_GeneralButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	switch(ButtonType)
	{
	case EMS_GeneralButtonType::Setting:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Setting));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::Menu:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Menu));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::Schedule:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Schedule));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::Manage:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Manage));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::OrderItem:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::OrderItem));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::CheckOrderItem:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::CheckOrderItem));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::BuyFurniture:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::BuyFurniture));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::HireStaff:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::HireStaff));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::StaffManage:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::StaffManage));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::CustomerManage:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::CustomerManage));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	case EMS_GeneralButtonType::SalesDetail:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::SalesDetail));
			CPP_Image->SetBrushFromTexture(Image);
			break;
		}
	default:
		{
			CPP_Image->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
	}
}