// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetType/TargetType_Sphere.h"
#include "Kismet/KismetSystemLibrary.h"

UTargetType_Sphere::UTargetType_Sphere()
{
	//OriginTransform = EEventDataVariableFilter::Instigator;
	Radius = -1;
	// TODO: Define default object types.
}


void UTargetType_Sphere::GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	if (!ensure(Instigator))
	{
		return;
	}


	if (EffectCauser == nullptr)
	{
		EffectCauser = Instigator->GetAvatarActor(); // Use instigator if no effect causer is specified.
	}

	FTransform OriginTransform = EffectCauser->GetActorTransform();

	if (OriginSocket != FName())
	{
		UMeshComponent* MeshComponent = EffectCauser->FindComponentByClass<UMeshComponent>();
		if (ensureAlways(MeshComponent))
		{
			OriginTransform = MeshComponent->GetSocketTransform(OriginSocket);
		}
	}

	FRotator Rotation;
	if (bUseEffectCauserRotation)
	{
		// Use weapon rotation.
		Rotation = OriginTransform.GetRotation().Rotator();
	}
	else
	{
		// Use character rotation.
		Rotation = Instigator->GetAvatarActor()->GetActorRotation();
	}
	

	FVector StartPoint = OriginTransform.GetLocation() + (Rotation.RotateVector(StartOffsetFromOrigin));

	FVector EndPoint = StartPoint + (Rotation.RotateVector(EndpointOffset));


	TArray<AActor*> IgnoreList;
	if (bIgnoreInstigator)
	{
		IgnoreList.Add(Instigator->GetOwner());
	}

	TArray<FHitResult> HitResults;

	UKismetSystemLibrary::SphereTraceMultiForObjects(EffectCauser, StartPoint, EndPoint, Radius, ObjectTypes, false, IgnoreList, bDebugVisualize ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResults, true);

	for (const FHitResult& IteratedHit : HitResults)
	{
		ETeamAttitude::Type CurrentAttitude = USambaGameplayStatics::GetAttitude(EffectCauser, IteratedHit.GetActor());
		if (TargetAttitudes.Contains(CurrentAttitude) == false)
		{
			continue;
		}

		OutActors.Add(IteratedHit.GetActor());
		OutHitResults.Add(IteratedHit);
		// Check attitude.
	}

}

