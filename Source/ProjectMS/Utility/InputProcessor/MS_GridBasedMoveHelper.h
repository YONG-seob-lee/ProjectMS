

#pragma once

#include "CoreMinimal.h"
#include <UObject/Object.h>
#include "MS_GridBasedMoveHelper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GridBasedMoveHelper : public UObject
{
	GENERATED_BODY()

public:
	UMS_GridBasedMoveHelper();

	const FVector2D& SetPositionOffset(class AActor* aTargetActor);

	void ResetPositionOffset();
	
	bool GetHitResultUnderObjectScreenPosition(const FVector2D& aPointerPostion, ECollisionChannel aTraceChannel, bool bTraceComplex, FHitResult& aOutHitResult) const;
	bool GetCheckedHitResultUnderObjectScreenPosition(class AActor* aTargetActor, const FVector2D& aPointerPostion, ECollisionChannel aTraceChannel, bool bTraceComplex, FHitResult& aOutHitResult) const;
	
	AActor* GetTargetActor() const { return TargetActor.Get(); }

	
private:
	TWeakObjectPtr<AActor> TargetActor;
	
	FVector2D PointerPostionToObjectScreenPositionOffset;
};
