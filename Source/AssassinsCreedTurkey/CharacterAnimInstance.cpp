// Copyright Fnd Game


#include "CharacterAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (TryGetPawnOwner())
	{
		SpeedCpp = TryGetPawnOwner()->GetVelocity().Size();
		bisFallingCpp = TryGetPawnOwner()->GetMovementComponent()->IsFalling();
	}
}
