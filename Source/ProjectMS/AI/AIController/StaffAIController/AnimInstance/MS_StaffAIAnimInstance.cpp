#include "AI/AIController/StaffAIController/AnimInstance/MS_StaffAIAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

UMS_StaffAIAnimInstance::UMS_StaffAIAnimInstance()
{
}

void UMS_StaffAIAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerInst = Cast<AMS_StaffAICharacter>(TryGetPawnOwner());
}

void UMS_StaffAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (GetWorld() == nullptr || OwnerInst == nullptr)
		return;

	OwnerMovementSpeed = OwnerInst->CharacterMovementComponent->Velocity.Length();
}

void UMS_StaffAIAnimInstance::SetOwnerWorkFlag(const bool& aWorkFlag)
{
	OwnerWorkFlag = aWorkFlag;
}
