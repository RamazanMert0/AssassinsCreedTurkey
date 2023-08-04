// Copyright Fnd Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Sword.generated.h"

UCLASS()
class ASSASSINSCREEDTURKEY_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();
	
	USceneComponent* Scene;
	UBoxComponent* Box;
	UPROPERTY(EditDefaultsOnly, Category = "Sword Mesh")
		UStaticMeshComponent* Sword_M;

	UFUNCTION()
	void Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
