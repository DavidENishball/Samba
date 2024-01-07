// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayEffectsVolumes/GameplayEffectsVolume.h"
#include "GEV_Sphere.generated.h"

class USphereComponent;
/**
 * A gameplay effect volume that is a sphere.
 */
UCLASS()
class SAMBA_API AGEV_Sphere : public AGameplayEffectsVolume
{
	GENERATED_BODY()
protected:

	AGEV_Sphere();
		
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USphereComponent* SphereComponent;

public:

	virtual void SetVolumeSize_Implementation(FVector NewSize) override;

};
