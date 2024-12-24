#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MS_StorageAssemblyAreaComponent.generated.h"

UCLASS() class PROJECTMS_API UMS_StorageAssemblyAreaComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UMS_StorageAssemblyAreaComponent(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual void OnComponentCreated() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	virtual void OnRegister() override;
	virtual void InitializeComponent() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditComponentMove(bool bFinished) override;
	virtual void PostEditUndo() override;

private:
	void DrawAssemblyAreaOutline();
	void RedrawAssemblyAreaOutline();
	void EraseAssemblyAreaOutline();
#endif

public:
	UFUNCTION(BlueprintCallable) FVector FindAdjacentLocationWithBay(int aBayOrder, class AMS_StaffAICharacter* aTarget);

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector AssemblyAreaSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FColor AssemblyAreaOutlineColor = FColor::Turquoise;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AssemblyAreaOutlineThickness = 1.0f;

	// Instance
public:
	class AMS_Storage* OwnerStorage = nullptr;
};
