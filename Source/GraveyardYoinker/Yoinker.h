// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Yoinker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVEYARDYOINKER_API UYoinker : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UYoinker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Yoink();

	UFUNCTION(BlueprintCallable)
	void Release();

private:

	UPROPERTY(EditAnywhere)
	float MaxYoinkDistance = 150;

	UPROPERTY(EditAnywhere)
	float YoinkRadius = 10;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 100;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
