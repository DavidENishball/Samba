// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/AbilityTasks/SambaAbilityTask.h"
#include <../../../../../../../Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h>
#include "../EffectPackage.h"
#include "SAT_GameplayEffectsVolume.generated.h"

/**
 * 
 */
UCLASS()
class SAMBA_API USAT_GameplayEffectsVolume : public USambaAbilityTask
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AGameplayEffectsVolume> VolumeClass;

	// Originate at this socket.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName OriginSocket;

	// Cover this socket by increasing X dimension.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName EndSocket;

	// Add this much extra to cover the Origin and End Socket.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EndSocketPadding;

	// The Size of the single volume.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector VolumeSize;

	// Attach offset from the origin location.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector OffsetLocationFromOrigin;

	// Rotate relative to origin.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator OffsetRotationFromOrigin;

	// If true, use the rotation of the owner's root component.  
	// If false, use the rotation of the socket.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUseRootRotation = false;

	// If true, the volume will attach to the socket and copy its rotation and location for its lifetime.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bAttachToSocket = true;

	// If false, the volume will persist until removed in some other way.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bDestroyVolumeWhenTaskEnds = true;

	// Automatically destroy the volume after this much time has passed.  Should only be used with bDestroyVolumeWhenTaskEnds is false.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "!bDestroyVolumeWhenTaskEnds"))
	float VolumeDuration = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter", meta = (ExposeOnSpawn))
	TArray<FEffectPackage> EffectPackagesAppliedOnEnter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<class UGameplayEffect>> EffectsOnEnter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Categories = "GameplayCue"))
	FGameplayTag CueOnActivation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bDebugDrawVolume = false;

protected:
	UPROPERTY()
	AGameplayEffectsVolume* SpawnedVolume;


	virtual void OnDestroy(bool AbilityEnded) override;
	virtual void Activate() override;

};
