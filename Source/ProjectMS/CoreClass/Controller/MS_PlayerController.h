#pragma once

#include "CoreMinimal.h"
#include "ProjectMS/Management/MS_Management.h"
#include "ProjectMS/Unit/MS_UnitBase.h"
#include "MS_PlayerController.generated.h"

UCLASS() class PROJECTMS_API AMS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMS_PlayerController();

	virtual void PostLoad() override;
	virtual void Tick(float aDeltaTime) override;

	void RegisterManagement();
	
	TObjectPtr<class AMS_CharacterBase> GetCharacterBase() const;
	TObjectPtr<class UMS_TableManager> GetTableManager() const;
	TObjectPtr<class UMS_UnitManager> GetUnitManager() const;
	TObjectPtr<class AMS_SceneManager> GetSceneManager() const;
	TObjectPtr<class UMS_WidgetManager> GetWidgetManager() const;
	FORCEINLINE class UInputMappingContext* GetInputMappingContext() { return MappingContext; }

protected:
	virtual void BeginPlay() override;
	
	// Instance
private:
	UPROPERTY() TObjectPtr<UMS_UnitBase> UnitBase = nullptr;
	UPROPERTY() TObjectPtr<UMS_Management> Management = nullptr;

	// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true")) class UInputMappingContext* MappingContext = nullptr;
};