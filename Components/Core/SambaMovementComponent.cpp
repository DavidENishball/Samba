// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Core/SambaMovementComponent.h"
#include <AbilitySystemComponent.h>
#include "GAS/AttributeSets/AttributeSet_Movement.h"
#include "GAS/TagDefinitions/SambaGameplayTags.h"

void USambaMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	ASC = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
}

float USambaMovementComponent::GetMaxSpeed() const
{
	float Multiplier = 1;
	bool bWasFound = false;
	
	if (ASC)
	{
		if (ASC->HasMatchingGameplayTag(TAG_Character_State_DisableMovement))
		{
			return 0;
		}
		Multiplier = ASC->GetGameplayAttributeValue(UAttributeSet_Movement::GetMoveSpeedMultiplierAttribute(), bWasFound);
	}

	switch (MovementMode)
	{
	case MOVE_Walking:
	case MOVE_NavWalking:
		return (bWasFound ? MaxWalkSpeed * Multiplier : MaxWalkSpeed);
	case MOVE_Falling:
		return MaxWalkSpeed;
	case MOVE_Swimming:
		return MaxSwimSpeed;
	case MOVE_Flying:
		return MaxFlySpeed;
	case MOVE_Custom:
		return MaxCustomMovementSpeed;
	case MOVE_None:
	default:
		return 0.f;
	}
}

float USambaMovementComponent::GetMinAnalogSpeed() const
{
	float Multiplier = 1;
	bool bWasFound = false;
	if (ASC)
	{
		if (ASC->HasMatchingGameplayTag(TAG_Character_State_DisableMovement))
		{
			return 0;
		}
		Multiplier = ASC->GetGameplayAttributeValue(UAttributeSet_Movement::GetMoveSpeedMultiplierAttribute(), bWasFound);
		if (bWasFound && Multiplier == 0)
		{
			return 0;
		}
	}

	return Super::GetMinAnalogSpeed();
}

// David N Note 11-22-2023 - Copying this from base class.
float GetAxisDeltaRotation(float InAxisRotationRate, float DeltaTime)
{
	// Values over 360 don't do anything, see FMath::FixedTurn. However we are trying to avoid giant floats from overflowing other calculations.
	return (InAxisRotationRate >= 0.f) ? FMath::Min(InAxisRotationRate * DeltaTime, 360.f) : 360.f;
}

FRotator USambaMovementComponent::GetDeltaRotation(float DeltaTime) const
{
	float Multiplier = 1.0f;
	bool bWasFound = false;

	if (ASC)
	{
		if (ASC->HasMatchingGameplayTag(TAG_Character_State_DisableTurning))
		{
			return FRotator::ZeroRotator;
		}
		Multiplier = ASC->GetGameplayAttributeValue(UAttributeSet_Movement::GetTurnSpeedMultiplierAttribute(), bWasFound);
	}

	return FRotator(GetAxisDeltaRotation(RotationRate.Pitch * Multiplier, DeltaTime), 
	GetAxisDeltaRotation(RotationRate.Yaw * Multiplier, DeltaTime), 
	GetAxisDeltaRotation(RotationRate.Roll * Multiplier, DeltaTime));
}
