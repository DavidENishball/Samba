// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayEffectsVolumes/GEV_Sphere.h"
#include "Components/SphereComponent.h"

AGEV_Sphere::AGEV_Sphere()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->VolumeComponents.Add(SphereComponent);
	RootComponent = SphereComponent;
	SphereComponent->SetGenerateOverlapEvents(true);
}

void AGEV_Sphere::SetVolumeSize_Implementation(FVector NewSize)
{
	SphereComponent->SetSphereRadius(NewSize.X);
}
