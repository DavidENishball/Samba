// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/SAT_GameplayEffectsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "../GameplayEffectsVolumes/GameplayEffectsVolume.h"
#include <../../../../../../../Source/Runtime/Core/Public/Math/RotationMatrix.h>

void USAT_GameplayEffectsVolume::OnDestroy(bool AbilityEnded)
{
	if (bDestroyVolumeWhenTaskEnds)
	{
		if (SpawnedVolume)
		{
			SpawnedVolume->Destroy();
		}
	}
}

void USAT_GameplayEffectsVolume::Activate()
{
	if (VolumeClass == nullptr)
	{
		return;
	}
	AActor* AvatarActor = GetAvatarActor();
	FTransform OriginTransform = GetAvatarActor()->GetActorTransform();

	bool bUseEndSocket = false;
	FTransform EndTransform;

	// TODO: encapsulate into Get Spawn Transform and Get Volume Size, so I can visualize it.

	//TODO:  EditCondition = "TheNameProperty.IsNone() == false" 
	if (OriginSocket.IsNone() == false)
	{
		UMeshComponent* MeshComponent = AvatarActor->FindComponentByClass<UMeshComponent>();
		if (ensureAlways(MeshComponent))
		{
			OriginTransform = MeshComponent->GetSocketTransform(OriginSocket);

			// Get end transform too.
			if (!EndSocket.IsNone())
			{
				EndTransform = MeshComponent->GetSocketTransform(EndSocket);
				bUseEndSocket = true;
			}
		}
	}

	FRotator Rotation;

	if (bUseEndSocket)
	{
		// Set rotation relative to End socket.  Forward is directly toward the end socket, up is the origin's Up vector.
		FVector ForwardVector = EndTransform.GetLocation() - OriginTransform.GetLocation();
		Rotation = FRotationMatrix::MakeFromXZ(ForwardVector, OriginTransform.GetRotation().GetUpVector()).Rotator();
	}
	else if (bUseRootRotation)
	{
		// Use character rotation.
		Rotation = GetAvatarActor()->GetActorRotation();
	}
	else
	{
		// Use socket rotation.
		Rotation = (OriginTransform.GetRotation().Rotator() + OffsetRotationFromOrigin);
	}
	FTransform SpawnTransform = OriginTransform;
	if (bUseEndSocket)
	{
		FVector AverageLocation = OriginTransform.GetLocation() + EndTransform.GetLocation() / 2;
		SpawnTransform.SetLocation(AverageLocation + (Rotation.RotateVector(OffsetLocationFromOrigin)));
	}
	else
	{
		SpawnTransform.SetLocation(OriginTransform.GetLocation() + (Rotation.RotateVector(OffsetLocationFromOrigin)));
	}

	SpawnedVolume = GetWorld()->SpawnActorDeferred<AGameplayEffectsVolume>(VolumeClass, SpawnTransform, AvatarActor, Cast<APawn>(AvatarActor), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (bUseEndSocket)
	{
		// Need to adjust volume size to conform to end socket.
		FVector CustomVolumeSize = VolumeSize;
		// Divide by two to account for half-size.
		CustomVolumeSize.X = ((EndTransform.GetLocation() - OriginTransform.GetLocation()).Size() / 2) + EndSocketPadding;
		SpawnedVolume->SetVolumeSize(VolumeSize);

	}
	else
	{
		// Use raw volume.
		SpawnedVolume->SetVolumeSize(VolumeSize);
	}


	SpawnedVolume->OwnerComponent = this->GetAbilitySystemComponent();
	SpawnedVolume->OwnerAbility = this->Ability;
	SpawnedVolume->GameplayEffectsAppliedOnEnter = EffectsOnEnter;
	SpawnedVolume->EffectPackagesAppliedOnEnter = EffectPackagesAppliedOnEnter;
	SpawnedVolume->CueOnActivation = CueOnActivation;

	if (bDebugDrawVolume)
	{
		SpawnedVolume->SetDebugDraw(true);
	}

	UGameplayStatics::FinishSpawningActor(SpawnedVolume, OriginTransform);
	if (bAttachToSocket)
	{
		// Assume it's already mid-way between origin socket and end socket, or directly centered on origin socket.
		FAttachmentTransformRules SomeRules = FAttachmentTransformRules::KeepWorldTransform;
		SomeRules.bWeldSimulatedBodies = true;
		SpawnedVolume->AttachToActor(AvatarActor, SomeRules, OriginSocket);
	}
}
