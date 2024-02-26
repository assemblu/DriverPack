// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RewindComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOURPORTAL_API URewindComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URewindComponent();

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// rewind event to be triggered by blueprints
	UFUNCTION(BlueprintCallable)
	void ERewind();

	UFUNCTION(BlueprintCallable)
	void ERecord();
};
