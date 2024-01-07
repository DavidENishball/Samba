// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/AttributeSet_Movement.h"
UAttributeSet_Movement::UAttributeSet_Movement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MoveSpeedMultiplier = 1.0f;
	TurnSpeedMultiplier = 1.0f;
}
