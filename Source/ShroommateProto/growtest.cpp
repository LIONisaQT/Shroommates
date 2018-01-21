
#include "Growtest.h"
#include "ShroommateProtoCharacter.h"
#include "Qualities3.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)


// Sets default values
AGrowtest::AGrowtest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set mesh of the growing area
	GrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrowMesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootMesh"));
	GrowMesh->SetupAttachment(RootComponent);

	//set hitbox
	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("hitbox"));
	//sethitboxsize
	Hitbox->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	Hitbox->bGenerateOverlapEvents = true;
	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AGrowtest::onPlayerEnter);
	Hitbox->OnComponentEndOverlap.AddDynamic(this, &AGrowtest::onPlayerExit);
	Hitbox->SetupAttachment(RootComponent);

	renderBox = CreateDefaultSubobject<UBoxComponent>(TEXT("renderbox"));
	renderBox->SetWorldScale3D(FVector(50.f, 50.f, 50.f));
	renderBox->bGenerateOverlapEvents = true;
	renderBox->OnComponentBeginOverlap.AddDynamic(this, &AGrowtest::onPlayerInRange);
	renderBox->OnComponentEndOverlap.AddDynamic(this, &AGrowtest::onPlayerOutRange);
	renderBox->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AGrowtest::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGrowtest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Controller = GetWorld()->GetFirstPlayerController();
	if (Controller != NULL) {
		if (Controller->IsInputKeyDown(EKeys::F)) {
			consume = 1;
		}
		else {
			consume = 0;
		}
	}

	if (consume && inConsumeRange && !eaten) {
		FVector NewScale = contact->GetActorScale();
		contact->SetActorRelativeScale3D(NewScale + FVector(0.005f, 0.005f, 0.005f));
		AShroommateProtoCharacter* tempChar = Cast<AShroommateProtoCharacter>(contact);
		UQualities3* tempq = tempChar->FindComponentByClass<UQualities3>();

		//for testing purposes
		tempq->addToHunger(change);
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		eaten = 1;
	}

	if (eaten) {
		respawn += DeltaTime;
	}

	if (respawn >= respawnTime) {
		eaten = 0;
		this->SetActorHiddenInGame(false);
		this->SetActorEnableCollision(true);
		respawn = 0.f;
	}

	if (inRenderRange) {
		GrowMesh->SetRenderCustomDepth(true);
	}
	else {

		GrowMesh->SetRenderCustomDepth(false);
	}
}

void AGrowtest::onPlayerEnter(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//debug
	if (OtherActor->GetName() == "Character") {
		contact = OtherActor;
		inConsumeRange = 1;
	}
}

void AGrowtest::onPlayerExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetName() == "Character") {
		inConsumeRange = 0;
	}
}

void AGrowtest::onPlayerInRange(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->GetName() == "Character") {
		inRenderRange = 1;
	}
}

void AGrowtest::onPlayerOutRange(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetName() == "Character") {
		inRenderRange = 0;
	}
}

