// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/TargetType/TargetType.h"
#include "TargetType_Sphere.generated.h"

/**
 * Target type that targets all units in a sphere.
 */
UCLASS()
class SAMBA_API UTargetType_Sphere : public UTargetType
{
	GENERATED_BODY()
public:

	UTargetType_Sphere();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName OriginSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Radius = -1;

	// Start is this far from the origin.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector StartOffsetFromOrigin;

	// If true, use the rotation of the effect causer (weapon).  If false, use the instigator (character).
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUseEffectCauserRotation = false;

	// Sweep this far from the Start.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector EndpointOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TEnumAsByte<	EObjectTypeQuery> > ObjectTypes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bDebugVisualize;

	virtual void GetTargets_Implementation(UAbilitySystemComponent* Instigator, AActor* EffectCauser, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};
