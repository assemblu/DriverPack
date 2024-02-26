// Fill out your copyright notice in the Description page of Project Settings.


#include "RewindComponent.h"

// Sets default values for this component's properties
URewindComponent::URewindComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URewindComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URewindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void URewindComponent::ERewind()
{
	if (!this->StateFrames.IsEmpty())
	{
		// get previous location
		FVector PreviousLocation = this->StateFrames.GetHead()->GetValue();
		GetOwner()->SetActorLocation(PreviousLocation, true);

		// pop rewinded location
		this->StateFrames.RemoveNode(this->StateFrames.GetHead());
		UE_LOG(LogTemp, Warning, TEXT("Rewind is complete"));
	}
	else
	{
		this->bIsRewinding = false;
		UE_LOG(LogTemp, Warning, TEXT("Rewind finished"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Rewind"));
}

void URewindComponent::ERecord()
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	if (!CurrentLocation.IsZero())
	{
		this->StateFrames.AddHead(CurrentLocation);
		if (this->StateFrames.Num() >= this->StateFrameSize)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pop oldest frame"));
			this->StateFrames.RemoveNode(this->StateFrames.GetTail());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Add frame"));
		}
	}
}
