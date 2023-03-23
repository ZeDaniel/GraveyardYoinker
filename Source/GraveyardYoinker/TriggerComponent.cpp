// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerComponent::AddBreaker(UBreaker* Breaker)
{
	Breakers.Add(Breaker);
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Mover != nullptr)
		CheckTriggerAndMove();

}

AActor* UTriggerComponent::GetAcceptableActorMover() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(AcceptableActorMoverTag) && !(Actor->ActorHasTag(ActorGrabbedTag)))
			return Actor;
	}
	return nullptr;
}

AActor* UTriggerComponent::GetAcceptableActorBreaker() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(AcceptableActorBreakerTag) && (Actor->ActorHasTag(ActorGrabbedTag)))
			return Actor;
	}
	return nullptr;
}

void UTriggerComponent::CheckTriggerAndMove()
{
	AActor* AcceptableActor = GetAcceptableActorMover();

	if (AcceptableActor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(AcceptableActor->GetRootComponent());
		if (Component != nullptr)
		{
			AcceptableActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Component->SetSimulatePhysics(false);
		}
		Mover->SetShouldMove(true);
	}
	else
		Mover->SetShouldMove(false);
}

void UTriggerComponent::CheckTriggerAndBreak()
{
	AActor* AcceptableActor = GetAcceptableActorBreaker();

	if (AcceptableActor != nullptr)
	{
		for (UBreaker* Breaker : Breakers)
		{
			Breaker->SetShouldBreak(true);
		}
	}

}
