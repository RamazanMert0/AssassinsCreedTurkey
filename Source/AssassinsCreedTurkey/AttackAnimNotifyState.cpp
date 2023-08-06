// Copyright Fnd Game

#include "DrawDebugHelpers.h"
#include "AttackAnimNotifyState.h"
#include "Sword.h"

void UAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
		FName SSwordName = "Sword_SLoc_S";
		FName ESwordName = "Sword_ELoc_S";
		FVector SSwordLoc = MeshComp->GetSocketLocation(SSwordName);
		FVector ESwordLoc = MeshComp->GetSocketLocation(ESwordName);
		FCollisionQueryParams Param;
		Param.AddIgnoredActor(ignorActor);
		FHitResult HitResult;GetWorld()->LineTraceSingleByChannel(HitResult, SSwordLoc, ESwordLoc, ECollisionChannel::ECC_Camera);
		DrawDebugLine(GetWorld(), SSwordLoc, ESwordLoc, FColor::Red);
}
