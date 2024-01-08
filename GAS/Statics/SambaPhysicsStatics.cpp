// Fill out your copyright notice in the Description page of Project Settings.


#include "SambaPhysicsStatics.h"


FRotator USambaPhysicsStatics::GetFlatRotation(FRotator Rotation)
{
	Rotation.Pitch = 0;
	Rotation.Roll = 0;
	return Rotation;
}

void USambaPhysicsStatics::FlattenRotationInPlace(FRotator& Rotation)
{
	Rotation.Pitch = 0;
	Rotation.Roll = 0;
}

FTransform USambaPhysicsStatics::GetFlatTransform(FTransform Transform)
{
	FRotator AsRotator = Transform.GetRotation().Rotator();
	FlattenRotationInPlace(AsRotator);
	Transform.SetRotation(AsRotator.Quaternion());
	return Transform;
}

void USambaPhysicsStatics::FlattenTransformInPlace(FTransform& Transform)
{
	FRotator AsRotator = Transform.GetRotation().Rotator();
	FlattenRotationInPlace(AsRotator);
	Transform.SetRotation(AsRotator.Quaternion());
}

void USambaPhysicsStatics::FlattenActorTransform(AActor* Actor)
{
	Actor->SetActorTransform(GetFlatTransform(Actor->GetActorTransform()));
}



FVector USambaPhysicsStatics::GetStandingLocation(const AActor* InActor, FVector FloorLocation)
{
	if (InActor == nullptr)
	{
		return FloorLocation;
	}
	UPrimitiveComponent* RootAsPrimitive = Cast<UPrimitiveComponent>(InActor->GetRootComponent());
	if (RootAsPrimitive == nullptr)
	{
		// Actor doesn't have any geometry or collision.
		return FloorLocation;
	}

	float HalfHeight = RootAsPrimitive->Bounds.BoxExtent.Z;

	FVector FinalLocation = FloorLocation + (FVector::UpVector * HalfHeight);
	return FinalLocation;
}

FVector USambaPhysicsStatics::GetActorBaseLocation(const AActor* InActor)
{
	if (InActor == nullptr)
	{
		return FVector::ZeroVector;
	}
	UPrimitiveComponent* RootAsPrimitive = Cast<UPrimitiveComponent>(InActor->GetRootComponent());
	if (RootAsPrimitive == nullptr)
	{
		// Actor doesn't have any geometry or collision.
		return FVector::ZeroVector;
	}

	float HalfHeight = RootAsPrimitive->Bounds.BoxExtent.Z;



	FVector FinalLocation = InActor->GetActorLocation() + (FVector::UpVector * HalfHeight * -1);
	return FinalLocation;
}
