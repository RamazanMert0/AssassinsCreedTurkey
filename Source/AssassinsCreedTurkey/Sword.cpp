// Copyright Fnd Game


#include "Sword.h"
#include "AssassinsCreedTurkeyCharacter.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneCompCpp"));
	Scene->SetupAttachment(GetRootComponent());
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompCpp"));
	Box->SetupAttachment(Scene);
	Sword_M = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMeshCompCpp"));
	Sword_M->SetupAttachment(Scene);

}

void ASword::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
			AAssassinsCreedTurkeyCharacter* Char = Cast<AAssassinsCreedTurkeyCharacter>(OtherActor);
			if (Char)
			{
				FName AttachName = "Sword_S";
				Sword_M->AttachTo(Char->GetMesh(), AttachName, EAttachLocation::SnapToTargetIncludingScale);
				Sword_M->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Char->bTakeSword = true;
			}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(2, 2.f, FColor::Red, TEXT("Character Yok"));
	}
}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASword::ASword::Overlap);
	
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

