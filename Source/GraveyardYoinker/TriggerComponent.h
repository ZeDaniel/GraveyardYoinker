// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "Breaker.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class GRAVEYARDYOINKER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTriggerComponent();

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

	UFUNCTION(BlueprintCallable)
	void AddBreaker(UBreaker* Breaker);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorMoverTag;

	UPROPERTY(EditAnywhere)
	FName AcceptableActorBreakerTag;

	UPROPERTY(EditAnywhere)
	FName ActorGrabbedTag;

	UMover* Mover;

	TArray<UBreaker*> Breakers;

	AActor* GetAcceptableActorMover() const;

	AActor* GetAcceptableActorBreaker() const;

	void CheckTriggerAndMove();
	
	void CheckTriggerAndBreak();

};
