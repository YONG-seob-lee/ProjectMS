// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "MS_SpawnPoint.generated.h"

namespace SpawnImage
{
	const FString PlayerPath = TEXT("/Engine/EditorResources/Ai_Spawnpoint.Ai_Spawnpoint");
	const FString PlayerName = TEXT("Player");
}
UCLASS()
class PROJECTMS_API AMS_SpawnPoint : public APlayerStart
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMS_SpawnPoint(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FName GetSpawnName() const { return SpawnName; }
private:
	UPROPERTY(EditAnywhere, Category = SpawnInfo, meta = (AllowPrivateAccess = "true"))
	FName SpawnName = FName();

	UPROPERTY(EditAnywhere, Category = SpawnInfo, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> SpriteImage = nullptr;
};
