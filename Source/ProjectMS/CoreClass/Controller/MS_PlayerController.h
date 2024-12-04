#pragma once

#include "CoreMinimal.h"
#include "ProjectMS/Management/MS_Management.h"
#include "ProjectMS/Unit/MS_UnitBase.h"
#include "MS_PlayerController.generated.h"

UCLASS()
class PROJECTMS_API AMS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMS_PlayerController();

	void RegisterManagement();
	
	virtual void Tick(float aDeltaTime) override;
	virtual void PostLoad() override;

	TObjectPtr<AMS_CharacterBase> GetCharacterBase() const;
	TObjectPtr<UMS_TableManager> GetTableManager() const;
	TObjectPtr<UMS_UnitManager> GetUnitManager() const;
	TObjectPtr<AMS_SceneManager> GetSceneManager() const;
	TObjectPtr<UMS_WidgetManager> GetWidgetManager() const;
	FORCEINLINE class UInputMappingContext* GetInputMappingContext() { return MappingContext; }

	inline FIntVector2 AcquireViewportSize();
	inline FVector2D AcquireMousePositionOnViewport();
	inline FVector2D AcquireTouchPositionOnViewport(ETouchIndex::Type aFingerIndex);

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UMS_UnitBase> UnitBase = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext = nullptr;
	
	UPROPERTY()
	TObjectPtr<UMS_Management> Management = nullptr;
};