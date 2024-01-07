// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayEffectsVolumes/GEV_Capsule.h"
#include "Components/CapsuleComponent.h"

AGEV_Capsule::AGEV_Capsule()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	this->VolumeComponents.Add(CapsuleComponent);
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetGenerateOverlapEvents(true);
}

void AGEV_Capsule::SetVolumeSize_Implementation(FVector NewSize)
{
	// X = Forward distance to new bone.
	// Y = lateral distance.
	CapsuleComponent->SetCapsuleSize(NewSize.Y, NewSize.X, true);
}
