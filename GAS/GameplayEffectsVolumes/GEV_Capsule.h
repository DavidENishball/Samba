// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayEffectsVolumes/GameplayEffectsVolume.h"
#include "GEV_Capsule.generated.h"

class UCapsuleComponent;
/**
 * A gameplay effect volume that is a Capsule.
 */
UCLASS()
class SAMBA_API AGEV_Capsule : public AGameplayEffectsVolume
{
	GENERATED_BODY()
protected:

	AGEV_Capsule();
		
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

public:

	virtual void SetVolumeSize_Implementation(FVector NewSize) override;

};
