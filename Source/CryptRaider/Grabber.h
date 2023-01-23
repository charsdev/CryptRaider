#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:
	UGrabber();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

private:
	UPhysicsHandleComponent* GetPhysicsHandle() const;
	bool GetGrababbleInReach(FHitResult& OutHitResult) const;

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance{ 400.0f };

	UPROPERTY(EditAnywhere)
	float GrabRadius{ 100.0f };

	UPROPERTY(EditAnywhere)
	float HoldDistance{ 200.0f };
};
