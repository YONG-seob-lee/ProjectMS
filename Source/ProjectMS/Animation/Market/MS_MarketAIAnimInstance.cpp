#include "MS_MarketAIAnimInstance.h"

void UMS_MarketAIAnimInstance::SetInAction(bool aInAction)
{
	bInAction = aInAction;
	OnChangeInActionDelegate.Broadcast(bInAction);
}
