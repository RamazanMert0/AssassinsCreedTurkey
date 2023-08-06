// Copyright Fnd Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character_PC.generated.h"

UCLASS()
class ASSASSINSCREEDTURKEY_API ACharacter_PC : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void CreateSession(int MaxPlayer);

	void Login();

};
