#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget/SubEditorUtilityWidget/XSubEditorUtilityWidget.h"
#include "XActorSpawnerSectionSubEditorUtilityWidget.generated.h"

UCLASS() class UXActorSpawnerSectionSubEditorUtilityWidget : public UXSubEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UXActorSpawnerSectionSubEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	TArray<UWorld*> CountPIEWorld();
	UFUNCTION() void OnSpawnEditorUtilityButtonClick();
	UFUNCTION() void OnUnspawnEditorUtilityButtonClick();

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UVerticalBox* ContentFrameVerticalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UDetailsView* ParameterDetailsView = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* SpawnEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* SpawnEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* UnspawnEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* UnspawnEditorUtilityButtonLabelTextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") FString LabelPrefix = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") FString Label = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") FVector Location = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") FRotator Rotation = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") FVector Scale = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") TSubclassOf<AActor> Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") TSoftObjectPtr<AActor> AttachmentActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") EAttachmentRule LocationAttachmentRule = EAttachmentRule::KeepRelative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") EAttachmentRule RotationAttachmentRule = EAttachmentRule::KeepRelative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") EAttachmentRule ScaleAttachmentRule = EAttachmentRule::KeepRelative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") bool WeldSimulatedBodiesFlag = false;
	static TArray<TSoftObjectPtr<AActor>> SpawnedActorArray;

	// Instance
public:
	class UEditorActorSubsystem* EditorActorSubsystemInst = nullptr;
};