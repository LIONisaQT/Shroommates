// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "ShroommateProtoCharacter.generated.h"

UCLASS(config=Game)
class AShroommateProtoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AShroommateProtoCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(Category = sound, EditAnywhere)
	class UAudioComponent* shroomAudio;

	UPROPERTY(Category = sound, EditAnywhere)
	class USoundCue* squishsquish;

	//AG 10/22/17: Clambor point stuff
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	bool onWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	bool justJumped;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float wallRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float timeSinceWallJump;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	bool canWall = false;

	//Skill Tree stuff
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		int skillpoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool agility1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool agility2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool agility3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool jump1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool jump2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool jump3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class ASkillTreeController* a;

	//UI stuff
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float MaxWater;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float CurrentWater;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		int Currency;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		int State;


	//jump
	float jump_gravity;
	float jump_height;
	float jump_control;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool canclimb;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool walkagain;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool movingW;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		bool movingR;


protected:

	virtual void BeginPlay() override;

	//Calls SkilltreeController function when you press U-key
	void OpenSkillTree();


	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

private:
	void SaveGame();
	void LoadGame();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetClimb(bool b);

	//UI
	void setMaxHealth(float MH);
	void setCurrentHealth(float CH);
	void setMaxWater(float MW);
	void setCurrentwater(float CW);
	void setCurrency(int C);
	void setState(int S);

	float getMaxHealth();
	float getCurrentHealth();
	float getMaxWater();
	float getCurrentWater();
	int getCurrency();
	int getState();
};

