#include "AI/Debug/MS_DebugRootUI.h"

UMS_DebugRootUI::UMS_DebugRootUI(const FObjectInitializer& aObjectInitializer) : Super(aObjectInitializer)
{
	bIsFocusable = true;
}

void UMS_DebugRootUI::NativeOnInitialized()
{
	SetVisibility(ESlateVisibility::Visible);
}

FReply UMS_DebugRootUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Unhandled();
}
