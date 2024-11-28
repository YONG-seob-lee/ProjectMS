// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	AMS_PlayerController();

	void RegisterManagement();
	
	virtual void Tick(float aDeltaTime) override;
	virtual void PostLoad() override;

	TObjectPtr<AMS_CharacterBase> GetCharacterBase() const;
	TObjectPtr<UMS_TableManager> GetTableManager() const;
	TObjectPtr<UMS_UnitManager> GetUnitManager() const;
	TObjectPtr<AMS_SceneManager> GetSceneManager() const;
	TObjectPtr<UMS_WidgetManager> GetWidgetManager() const;
	FORCEINLINE TObjectPtr<class UInputMappingContext> GetInputMappingContext() { return DefaultMappingContext; }

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UMS_UnitBase> UnitBase = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY()
	TObjectPtr<UMS_Management> Management = nullptr;
};
