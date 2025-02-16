// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AIUnit.h"

#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "Character/MS_CharacterBase.h"

namespace AIBlueprintPath
{
	const FString OutsideAI = TEXT("/Game/Unit/BP_OutsideAICharacter.BP_OutsideAICharacter_C");
}

void UMS_AIUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aUnitTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aUnitTableId);
}

void UMS_AIUnit::Finalize()
{
	DestroyUnitActor();
	
	if(AIController)
	{
		GetWorld()->DestroyActor(AIController);
		MS_DeleteObject(AIController);
		AIController = nullptr;
	}
	
	Super::Finalize();
}

void UMS_AIUnit::PostInitialize()
{
	Super::PostInitialize();

	const TObjectPtr<ACharacter> AICharacter = GetCharacter();
	if(!AICharacter)
	{
		return;
	}
	AIController = Cast<AMS_AIController>(AICharacter->GetController());
	if(AIController)
	{
		AIController->Initialize();
		BlackboardComponent = AIController->GetBlackboardComponent();
	}
}

UClass* UMS_AIUnit::GetBlueprintClass() const
{
	UClass* BPClass = StaticLoadClass(UObject::StaticClass(), nullptr, *AIBlueprintPath::OutsideAI);
	if(!IsValid(BPClass))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] BPClass is invalid (BPPath : %s)"), *MS_FUNC_STRING, *AIBlueprintPath::OutsideAI);

		return nullptr;
	}

	return BPClass;
}
