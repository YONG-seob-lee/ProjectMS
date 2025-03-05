#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "MS_CustomerAICharacter.generated.h"

enum class EMS_PickUpSocketType
{
	None = 0,
	Head = 1,
	LeftHand = 2,
	RightHand = 3,
};
namespace ItemEquipment
{
	const FString Path = TEXT("/Game/Blueprints/Equipment/BP_ItemEquipment.BP_ItemEquipment_C");
}
UCLASS()
class PROJECTMS_API AMS_CustomerAICharacter : public AMS_MarketAICharacter
{
	GENERATED_BODY()
	
public:
	AMS_CustomerAICharacter();

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
	
	void PickUp(int32 ItemTableId);
	void ShowPickUp(bool bShow);

private:
	UPROPERTY()
	TMap<int32, TObjectPtr<class AMS_ItemEquipment>> PickUpSockets;
	
	UPROPERTY()
	TMap<int32, TObjectPtr<class UStaticMesh>> Items;
};
