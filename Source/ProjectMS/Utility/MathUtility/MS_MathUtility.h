#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_MathUtility.generated.h"

UENUM()
enum class EMS_InterpolationType
{
	Undefined,
	EaseIn,
	EaseOut,
	Linear
};

UCLASS()
class UMS_MathUtility : public UObject
{
	GENERATED_BODY()

public:
	UMS_MathUtility() = default;

	static float CalculateInterpolation(float aProgressRate, EMS_InterpolationType aInterplationType, int aExponent = 2.0f)
	{
		float Result = 0.0f;

		switch (aInterplationType)
		{
		case EMS_InterpolationType::Undefined:
		{
			Result = 0.0f;
			break;
		}
		case EMS_InterpolationType::EaseIn:
		{
			Result = 1.0f - cosf(FMath::Lerp(0.0f, PI / aExponent, aProgressRate));
			break;
		}
		case EMS_InterpolationType::EaseOut:
		{
			Result = sinf(FMath::Lerp(0.0f, PI / aExponent, aProgressRate));
			break;
		}
		case EMS_InterpolationType::Linear:
		{
			Result = aProgressRate;
			break;
		}
		default:
		{
			break;
		}
		}

		return Result;
	}
};