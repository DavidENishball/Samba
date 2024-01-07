// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SambaMovementComponent.generated.h"

class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SAMBA_API USambaMovementComponent : public UCharacterMovementComponent
{

	GENERATED_BODY()

	

	void BeginPlay() override;

	//BEGIN UMovementComponent Interface
	 float GetMaxSpeed() const override;

	 // Ensures that if our speed is 0 we do not move.
	 float GetMinAnalogSpeed() const override;

	 /** Returns how far to rotate character during the time interval DeltaTime. */
	 virtual FRotator GetDeltaRotation(float DeltaTime) const override;
	//END UMovementComponent Interface

		protected:
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* ASC;
};
