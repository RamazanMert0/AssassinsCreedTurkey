// Copyright Fnd Game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

UCLASS()
class ASSASSINSCREEDTURKEY_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	float SpeedCpp;
	UPROPERTY(BlueprintReadOnly)
	bool bisFallingCpp;
};
