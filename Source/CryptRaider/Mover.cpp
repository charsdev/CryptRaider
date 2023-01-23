#include "Mover.h"

UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector TargetLocation{ OriginalLocation };

	if (bShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
	}

	FVector CurrentLocation{ GetOwner()->GetActorLocation() };
	double Speed{ MoveOffset.Size() / MoveTime };
	FVector NewLocation{ FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed) };
	GetOwner()->SetActorLocation(NewLocation);
}

void UMover::SetShouldMove(bool bNewShouldMove)
{
	bShouldMove = bNewShouldMove;
}