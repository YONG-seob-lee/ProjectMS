// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralButton.h"

#include "Components/Image.h"

namespace ImagePath
{
	const FString Setting = TEXT("/Game/UI/Image/Icon/SettingIcon.SettingIcon");
	const FString Menu = TEXT("/Game/UI/Image/Icon/MenuIcon.MenuIcon");
	const FString Schedule = TEXT("/Game/UI/Image/Icon/BoardIcon.BoardIcon");
	const FString Manage = TEXT("/Game/UI/Image/Icon/ManageIcon.ManageIcon");
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
			//GetOnClickedDelegate().AddUObject(this, &UMS_GeneralButton::OnClickedSettingButton);
			break;
		}
	case EMS_GeneralButtonType::Menu:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Menu));
			CPP_Image->SetBrushFromTexture(Image);
			//GetOnClickedDelegate().AddUObject(this, &UMS_GeneralButton::OnClickedMenuButton);
			break;
		}
	case EMS_GeneralButtonType::Schedule:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Schedule));
			CPP_Image->SetBrushFromTexture(Image);
			//GetOnClickedDelegate().AddUObject(this, &UMS_GeneralButton::OnClickedScheduleButton);
			break;
		}
	case EMS_GeneralButtonType::Manage:
		{
			CPP_Image->SetVisibility(ESlateVisibility::HitTestInvisible);
			UTexture2D* Image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath::Manage));
			CPP_Image->SetBrushFromTexture(Image);
			//GetOnClickedDelegate().AddUObject(this, &UMS_GeneralButton::OnClickedManageButton);
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
	default:
		{
			CPP_Image->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
	}
}

void UMS_GeneralButton::OnClickedSettingButton()
{
}

void UMS_GeneralButton::OnClickedMenuButton()
{
}

void UMS_GeneralButton::OnClickedScheduleButton()
{
}

void UMS_GeneralButton::OnClickedManageButton()
{
}
