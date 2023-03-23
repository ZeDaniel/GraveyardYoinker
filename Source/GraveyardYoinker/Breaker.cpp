// Fill out your copyright notice in the Description page of Project Settings.


#include "Breaker.h"

// Sets default values for this component's properties
UBreaker::UBreaker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBreaker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBreaker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldBreak)
		Break();
}

void UBreaker::SetShouldBreak(bool NewShouldBreak)
{
	ShouldBreak = NewShouldBreak;
}

void UBreaker::Break()
{
	AActor* Owner = GetOwner();

	//Hide Actor
	Owner->SetActorHiddenInGame(true);

	//Disable collision
	Owner->SetActorEnableCollision(false);

	//Stop Actor ticking
	Owner->SetActorTickEnabled(false);
}

