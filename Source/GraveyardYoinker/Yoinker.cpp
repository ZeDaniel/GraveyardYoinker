// Fill out your copyright notice in the Description page of Project Settings.


#include "Yoinker.h"

#include "Engine/World.h" 
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UYoinker::UYoinker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UYoinker::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UYoinker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
		return;
	
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UYoinker::Yoink()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
		return;

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	
}

void UYoinker::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
		return;

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UYoinker::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Yoinker requires a UPhysics Object"));
	}
	return PhysicsHandle;	
}

bool UYoinker::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxYoinkDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(YoinkRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}

