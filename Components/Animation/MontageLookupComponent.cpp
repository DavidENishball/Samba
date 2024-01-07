// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Animation/MontageLookupComponent.h"
#include "AnimMontageSelector.h"
#include <GameplayEffectTypes.h>
#include <GameplayTagContainer.h>

// Sets default values for this component's properties
UMontageLookupComponent::UMontageLookupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UMontageLookupComponent::BeginPlay()
{
	Super::BeginPlay();

	// Automatically cache the skeletal mesh.
	CachedSkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

UAnimMontage* UMontageLookupComponent::LookupMontage(const FGameplayTag& Tag, const FGameplayEffectContextHandle& ContextHandle) const
{
	UAnimMontage* OutMontage = nullptr;
	UAnimMontageSelector* ChosenSelector = MontageSelectorMap.FindRef(Tag);

	if (ChosenSelector)
	{
		OutMontage = ChosenSelector->SelectMontageByEventContext(CachedSkeletalMesh, Tag, ContextHandle);
	}

	return OutMontage;
}

void UMontageLookupComponent::InitializeComponent()
{
	// Set default selectors.
}
