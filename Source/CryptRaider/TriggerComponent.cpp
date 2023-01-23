#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Actor { GetAcceptableActor() };

	if (Actor) 
	{
		UPrimitiveComponent* Component { Cast<UPrimitiveComponent>(Actor->GetRootComponent()) };
		if (Component) 
		{
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else 
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover *NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors; 
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		bool bHasAcceptableTag { Actor->ActorHasTag(AcceptableTag) };
        bool bIsGrabbed { Actor->ActorHasTag("Grabbed") };

		if (bHasAcceptableTag && !bIsGrabbed)
        {
            return Actor;
        }
	}
    return nullptr;
}
