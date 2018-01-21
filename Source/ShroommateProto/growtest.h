// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Growtest.generated.h"

UCLASS()
class SHROOMMATEPROTO_API AGrowtest : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GrowMesh;

	//set pickup hitbox
	UPROPERTY(EditAnywhere)
		class UShapeComponent* Hitbox;
	//set render box 
	UPROPERTY(EditAnywhere)
		class UShapeComponent* renderBox;

	UPROPERTY(Category = Qualities, EditAnywhere)
		float change; //AG 10/15/17: How much it affects the attribute 

	UPROPERTY(Category = Type, EditAnywhere)
		TArray<FString> Type = { TEXT("Hunger"), TEXT("Humidity"), TEXT("Light") };

public:
	// Sets default values for this actor's properties
	AGrowtest();

	APlayerController* Controller;

	//bool for key press interaction if needed
	bool consume = 0;
	bool inConsumeRange = 0;
	bool eaten = 0;
	AActor* contact;

	float respawn = 0.f;
	UPROPERTY(Category = Gameplay, EditAnywhere)
		float respawnTime = 60.f;
	//boolean for custom render pass
	bool inRenderRange = 0;
	//set mesh component


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void onPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void onPlayerExit(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void onPlayerInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void onPlayerOutRange(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

