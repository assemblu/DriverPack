// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Containers/RingBuffer.h"
#include "Logging/LogMacros.h"
#include "HourportalCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class AHourportalCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent *FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *LookAction;

public:
	// variables

	// fires Rewind event
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRewinding = false;

	// when enabed, frames will be recorded
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRecordingFrames = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecordFrameSpeed = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RewindFrameSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StateFrameSize = 1000000;

	int StateFrameCount = 0;

	// rewind frames
	TDoubleLinkedList<FVector> StateFrames;

public:
	// functions

	AHourportalCharacter();

	// rewind event to be triggered by blueprints
	UFUNCTION(BlueprintCallable)
	void ERewind();

	UFUNCTION(BlueprintCallable)
	void ERecord();

	UFUNCTION(BlueprintCallable)
	void LogPrinter();
	

protected:
	/** Called for movement input */
	void Move(const FInputActionValue &Value);

	/** Called for looking input */
	void Look(const FInputActionValue &Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent *GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent *GetFollowCamera() const { return FollowCamera; }
};
